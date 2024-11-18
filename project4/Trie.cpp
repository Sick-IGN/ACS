#include "Trie.h"

size_t hash(char c) {
  return c - 'a';
};

TrieNode::TrieNode() : index(-1) {
  for (int i = 0; i < 26; i++) {
    children[i] = nullptr;
  }
};

void Trie::deleteNode(TrieNode* node) {
  if (node == nullptr) return;

  for (int i = 0; i < 26; i++) {
    if (node->children[i] != nullptr) {
      deleteNode(node->children[i]);
      node->children[i] = nullptr;
    }
  }
  delete node;
};

Trie::Trie() : cnt(0) {
  root = new TrieNode();
};

Trie::~Trie() {
  deleteNode(root);
};

size_t Trie::insert(const std::string& word) {

  TrieNode* node = root;

  size_t exists = search(word);
  if (exists != -1) return exists;

  for (char c : word) {
    int i = hash(c);

    if (node->children[i] == nullptr) {
      node->children[i] = new TrieNode();
    }

    node = node->children[i];
  }

  node->index = cnt;
  cnt += 1;
  return node->index;
};

size_t Trie::search(const std::string& word) const {
  
  TrieNode* node = root;

  for (char c : word) {
    int i = hash(c);

    if (node->children[i] == nullptr) {
      return -1;
    } 
    
    node = node->children[i];
  }

  return node->index != -1 ? node->index : 1;

};

size_t Trie::SIMDSearch(const std::string& word) const {
  TrieNode* node = root;

  for (char c : word) {
    // Load the characters from all children into a SIMD register
    __m256i child_chars = _mm256_setzero_si256(); // Initialize with zeros
    char values[26];
    int child_indices[26];

    // Extract all active children characters and their indices
    for (int i = 0; i < 26; i++) {
      values[i] = (node->children[i] != nullptr) ? 'a' + i : 0;
      child_indices[i] = (node->children[i] != nullptr) ? i : -1;
    }

    // Load the children characters into a SIMD register
    child_chars = _mm256_loadu_si256((__m256i*)values);

    // Broadcast the target character to a SIMD register
    __m256i target_char = _mm256_set1_epi8(c);

    // Perform the comparison
    __m256i cmp_result = _mm256_cmpeq_epi8(child_chars, target_char);

    // Convert the comparison result to a bitmask
    int mask = _mm256_movemask_epi8(cmp_result);

    // Check for a match
    if (mask == 0) {
      return -1; // No match found
    }

    // Find the first matching index
    int match_index = __builtin_ctz(mask); // Count trailing zeros to find the match
    if (child_indices[match_index] == -1) {
      return -1; // No valid child at this index
    }

    // Move to the corresponding child node
    node = node->children[child_indices[match_index]];
  }

  return node->index != -1 ? node->index : -1;
};

void Trie::loadFromFile(const std::string& filename) {

  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error, file didnt work" << std::endl;
    return;
  }

  std::string word;
  
  while (std::getline(file, word)) {
    insert(word.substr(0, word.size() -1));
  }

  file.close();
  std::cout << "loaded successfully" << std::endl;
};

void Trie::threadedLoad(const std::string& filename, int numThreads) {

  std::ifstream file(filename, std::ios::in | std::ios::binary);

  if (!file.is_open()) {
      std::cerr << "Error, file didnt work" << std::endl;
      return;
  }

  file.seekg(0, std::ios::end);
  long file_size = file.tellg();
  file.seekg(0, std::ios::beg);

  long chunk_size = file_size / numThreads;

  std::vector<std::thread> threads;
  std::vector<std::vector<std::string>> chunks(numThreads);
  std::mutex mtx;

  for (size_t i = 0; i < numThreads; i++) {
    long start = i * chunk_size;
    long end = (i == numThreads-1) ? file_size : (i+1) * chunk_size;

    threads.emplace_back(&Trie::readChunk, this, std::ref(file), start, end, std::ref(chunks[i]));
  }

  for (auto& t : threads) {
    t.join();
  }

  threads.clear();
  for (size_t i = 0; i < numThreads; i++) {
    threads.emplace_back(&Trie::insertBatch, this, std::ref(chunks[i]), std::ref(mtx));
  }

  for (auto& t : threads) {
    t.join();
  }

  std::cout << "Threaded load completed" << std::endl;

}

void Trie::printTrie() const {
    std::string currentWord;
    printTrieHelper(root, currentWord);
}

void Trie::printTrieHelper(TrieNode* node, std::string& currentWord) const {
    if (node == nullptr) {
        return;
    }

    // If the node contains a valid index, print the word and its index
    if (node->index != -1) {
    std::cout << currentWord << " -> Index: " << node->index << std::endl;
    }

    // Recursively visit each child
    for (int i = 0; i < 26; ++i) {
        if (node->children[i] != nullptr) {
            // Append the current character to the word
            currentWord.push_back('a' + i);
            // Recursively call the helper function
            printTrieHelper(node->children[i], currentWord);
            // Backtrack after the recursive call
            currentWord.pop_back();
        }
    }
}

void Trie::insertBatch(std::vector<std::string>& words, std::mutex& mtx) {
    // This function will insert a batch of words into the Trie
    for (const auto& word : words) {
        std::lock_guard<std::mutex> lock(mtx); // Protect shared resource (Trie)
        insert(word);
    }
}

void Trie::readChunk(std::ifstream& file, long start, long end, std::vector<std::string>& chunk) {
    // Move the file pointer to the start position
    file.seekg(start, std::ios::beg);

    std::string line;
    while (file.tellg() < end && std::getline(file, line)) {
        // Remove the carriage return if present
        if (!line.empty() && line.back() == '\r') {
            line = line.substr(0, line.size() - 1); // Strip the carriage return
        }
        chunk.push_back(line);
    }
}

void Trie::collectWords(TrieNode* node, std::vector<size_t>& result) const {

  if (node->index != -1) {
    result.push_back(node->index);
  }

  for (size_t i = 0; i < 26; ++i) {
    if (node->children[i] != nullptr) {
      collectWords(node->children[i], result);
    }
  }

}

std::vector<size_t> Trie::prefixSearch(const std::string& prefix) const {
  std::vector<size_t> result;

  TrieNode* node = root;

  for (char c : prefix) {
    size_t i = hash(c);

    if (node->children[i] == nullptr) {
      return result;
    }
    
    node = node->children[i];
  }

  collectWords(node, result);
  return result;
}