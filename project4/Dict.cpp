#include "Dict.h"

Dict::Dict() {
  trie = new Trie();
}

Dict::~Dict() {
  delete trie;
}

void Dict::loadFromFile(const std::string& filename) {

  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error, file didnt work" << std::endl;
    return;
  }

  std::string word;
  
  while (std::getline(file, word)) {
    size_t index = trie->insert(word.substr(0, word.size() -1));
    datastore[index] = word.substr(0, word.size() -1);
  }

  file.close();
  std::cout << "loaded successfully" << std::endl;
};

void Dict::threadedLoad(const std::string& filename, int numThreads) {

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

    threads.emplace_back(&Dict::readChunk, this, std::ref(file), start, end, std::ref(chunks[i]));
  }

  for (auto& t : threads) {
    t.join();
  }

  threads.clear();
  for (size_t i = 0; i < numThreads; i++) {
    threads.emplace_back(&Dict::insertBatch, this, std::ref(chunks[i]), std::ref(mtx));
  }

  for (auto& t : threads) {
    t.join();
  }

  std::cout << "Threaded load completed" << std::endl;

}

void Dict::insertBatch(std::vector<std::string>& words, std::mutex& mtx) {
  for (const auto& word : words) {
    std::lock_guard<std::mutex> lock(mtx); 
    size_t index = trie->insert(word);
    datastore[index] = word;
  }
}

void Dict::readChunk(std::ifstream& file, long start, long end, std::vector<std::string>& chunk) {
  file.seekg(start, std::ios::beg);

  std::string line;
  while (file.tellg() < end && std::getline(file, line)) {
    if (!line.empty() && line.back() == '\r') {
      line = line.substr(0, line.size() - 1); 
    }
    chunk.push_back(line);
  }
}

size_t Dict::search(const std::string& str) const {
  return trie->search(str);
}

std::vector<size_t> Dict::prefixSearch(const std::string& prefix) const {
  return trie->prefixSearch(prefix);
}

std::string Dict::returnString(const size_t index) const {
  return datastore.at(index);
}

void Dict::genDictFile(const std::string& filename) const {
  std::ofstream outFile(filename);

  if (!outFile.is_open()) {
    std::cerr << "file didnt load" << std::endl; 
    return;
  }

  for (const auto& entry : datastore) {
    size_t i = entry.first;
    const std::string& word = entry.second;
    outFile << i << '\t' << word << '\n';
  }

  outFile.close();
  std::cout << "Dict file saved" << std::endl;
}

void Dict::writeChunk(const std::unordered_map<size_t, std::string>& chunk, std::ofstream& outFile) const {
  for (const auto& entry : chunk) {
    size_t i = entry.first;
    const std::string& word = entry.second;
    outFile << i << '\t' << word << '\n';
  }
}

void Dict::threadedGenFile(const std::string& filename, const size_t numThreads) const {
  size_t chunkSize = datastore.size() / numThreads;
  std::vector<std::thread> threads;
  std::vector<std::unordered_map<size_t, std::string>> chunks(numThreads);
  std::mutex filemtx;

  auto it = datastore.begin();
  
  for (size_t t = 0; t < numThreads; ++t) {
    size_t currentChunkSize = (t == numThreads - 1) ? datastore.size() - (t * chunkSize) : chunkSize;

    for (size_t i = 0; i < currentChunkSize; ++i, ++it) {
      chunks[t][it->first] = it->second;
    }
  }
  for (size_t t = 0; t < numThreads; ++t) {

    threads.emplace_back([this, &chunks, t, &filemtx, &filename]() {
      std::ofstream outFile(filename, std::ios::app);

      if (!outFile.is_open()) {
        std::cerr << "file no open" << std::endl;
        return;
      }

      std::lock_guard<std::mutex> lock(filemtx);
      writeChunk(chunks[t], outFile);
      outFile.close();
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  std::cout << "done creating dict" << std::endl;
}

void Dict::encodeFile(const std::string& inFile, const std::string& outFile, const size_t numThreads) const {
  std::ifstream inputFile(inFile);
  if (!inputFile.is_open()) {
    std::cerr << "err opening input" << std::endl;
  }

  inputFile.seekg(0, std::ios::end);
  long file_size = inputFile.tellg();
  inputFile.seekg(0, std::ios::beg);

  long chunk_size = file_size / numThreads;

  std::vector<std::vector<std::string>> encodedChunks(numThreads);

  std::vector<std::thread> threads;
  for (size_t i = 0; i < numThreads; ++i) {
    long start = i * chunk_size;
    long end = (i == numThreads - 1) ? file_size : (i + 1) * chunk_size;

    threads.emplace_back([this, &encodedChunks, i, inFile, start, end]() {
      std::ifstream threadFile(inFile, std::ios::in);
      if (!threadFile.is_open()) {
        std::cerr << "file no open" << std::endl;
        return;
      }

      threadFile.seekg(start);
      std::string line;
      while (threadFile.tellg() < end && std::getline(threadFile, line)) {
        if (search(line) != -1) {
          encodedChunks[i].push_back(std::to_string(search(line))); 
        }
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  std::ofstream outputFile(outFile, std::ios::out | std::ios::binary);
  if (!outputFile.is_open()) {
    std::cerr << "gg file" << std::endl;
    return;
  }

  for (const auto& chunk : encodedChunks) {
    for (const std::string& str : chunk) {
      outputFile.write(str.c_str(), str.size());
      outputFile.put('\n');
    }
  }

  outputFile.close();
  std::cout << "encoding done" << std::endl;
}

void Dict::decodeFile(const std::string& inFile, const std::string& outFile, const size_t numThreads) const {
    // Open the input file
    std::ifstream inputFile(inFile, std::ios::in | std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return;
    }

    // Determine file size
    inputFile.seekg(0, std::ios::end);
    long file_size = inputFile.tellg();
    if (file_size == 0) {
        std::cerr << "Input file is empty!" << std::endl;
        return;
    }
    inputFile.seekg(0, std::ios::beg);

    // Calculate chunk size
    long chunk_size = file_size / numThreads;

    // Vector to store results from all threads
    std::vector<std::vector<std::string>> decodedChunks(numThreads);

    // Lambda for each thread to decode its chunk
    auto decodeChunk = [this](const std::string& inFile, long start, long end, std::vector<std::string>& outputChunk) {
        std::ifstream threadFile(inFile, std::ios::in | std::ios::binary);
        if (!threadFile.is_open()) {
            std::cerr << "Error opening input file in thread" << std::endl;
            return;
        }

        threadFile.seekg(start);

        std::string line;
        while (threadFile.tellg() < end && std::getline(threadFile, line)) {
            try {
                size_t index = std::stoull(line);  // Convert the line to an index
                outputChunk.push_back(returnString(index));  // Decode the index
            } catch (const std::exception& e) {
                std::cerr << "Error decoding line: " << e.what() << std::endl;
            }
        }
    };

    // Launch threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < numThreads; ++i) {
        long start = i * chunk_size;
        long end = (i == numThreads - 1) ? file_size : (i + 1) * chunk_size;

        threads.emplace_back(decodeChunk, inFile, start, end, std::ref(decodedChunks[i]));
    }

    // Wait for threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Write results to the output file sequentially
    std::ofstream outputFile(outFile, std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return;
    }

    for (const auto& chunk : decodedChunks) {
        for (const auto& str : chunk) {
            outputFile << str << '\n';
        }
    }

    std::cout << "Decoding completed successfully." << std::endl;
}


void Dict::genPairs(const std::string& inFile, const std::string& outFile, size_t numThreads) const {
    std::ifstream inputFile(inFile);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return;
    }

    inputFile.seekg(0, std::ios::end);
    size_t file_size = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    
    size_t chunk_size = file_size / numThreads;
    std::vector<std::thread> threads;
    std::mutex mtx;

    std::ofstream outputFile(outFile);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return;
    }

    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == numThreads - 1) ? file_size : (i + 1) * chunk_size;
        threads.emplace_back(&Dict::processChunk, this, inFile, start, end, std::ref(outputFile), std::ref(mtx));
    }

    for (auto& t : threads) {
        t.join();
    }

    outputFile.close();  
    std::cout << "gen pairs done" << std::endl;
}

void Dict::processChunk(const std::string& inFile, size_t start, size_t end, std::ofstream& outputFile, std::mutex& mtx) const {
  std::ifstream inputFile(inFile);
  inputFile.seekg(start);

  size_t index;
  std::string line;
  while (inputFile.tellg() < end && std::getline(inputFile, line)) {
    std::lock_guard<std::mutex> lock(mtx);
    index = search(line);
    if (index != -1) {
      outputFile << std::to_string(index) << "\t" << line << std::endl; 
    }
  }
}

std::vector<size_t> Dict::searchFromEncodedFile(const std::string& str, const std::string& filename) const {
  std::vector<size_t> resultIndices;

  std::ifstream file(filename, std::ios::in | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error opening encoded file" << std::endl;
    return resultIndices; 
  }
  std::string line;
  while (std::getline(file, line)) {
    size_t index = std::stoull(line);  
    
    if (datastore.count(index) && datastore.at(index) == str) {
      resultIndices.push_back(index);  
    }
  }

  file.close();
  return resultIndices; 
}

std::vector<size_t> Dict::prefixSearchFromEncodedFile(const std::string& str, const std::string& filename) const {
    std::vector<size_t> resultIndices;

    // Open the encoded file for reading
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening encoded file" << std::endl;
        return resultIndices;  // Return empty vector if file can't be opened
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        // The line should contain a size_t index followed by the word (or just the index if only indexes are stored)
        size_t index = std::stoull(line);  // Convert the line to a size_t (index)

        // Check if the index exists in the datastore and if the word starts with the given prefix
        if (datastore.count(index) && datastore.at(index).find(str) == 0) {  // .find() returns 0 if prefix matches
            resultIndices.push_back(index);  // Add the index to the result if it matches the prefix
        }
    }

    file.close();
    return resultIndices;  // Return all matching indices found in the file
}

std::vector<size_t> Dict::SIMDPrefixSearchFromEncodedFile(const std::string& prefix, const std::string& filename) const {
    std::vector<size_t> resultIndices;

    // Open the file for reading
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening encoded file" << std::endl;
        return resultIndices;
    }

    size_t prefixLength = prefix.size();
    const size_t AVX_REGISTER_SIZE = 32;

    // Prepare aligned prefix buffer for SIMD
    alignas(32) char prefixAligned[AVX_REGISTER_SIZE] = {};
    std::memcpy(prefixAligned, prefix.c_str(), std::min(prefixLength, AVX_REGISTER_SIZE));

    std::string line;
    while (std::getline(file, line)) {
        // Read the index from the file
        size_t index = std::stoull(line);

        // Check if the index exists in the datastore
        if (datastore.count(index)) {
            const std::string& word = datastore.at(index);

            // Check for prefix match
            bool match = true;
            for (size_t i = 0; i < prefixLength; i += AVX_REGISTER_SIZE) {
                alignas(32) char wordChunk[AVX_REGISTER_SIZE] = {};

                // Determine the size of the current chunk
                size_t chunkSize = std::min(AVX_REGISTER_SIZE, prefixLength - i);

                // Copy the relevant chunk from the word, ensuring no out-of-bounds access
                if (i < word.size()) {
                    size_t copySize = std::min(chunkSize, word.size() - i);
                    std::memcpy(wordChunk, word.data() + i, copySize);
                }

                // Load data into AVX registers
                __m256i wordVec = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wordChunk));
                __m256i prefixVec = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(prefixAligned));
                __m256i result = _mm256_cmpeq_epi8(wordVec, prefixVec);

                // Create a bitmask of the comparison results
                int mask = _mm256_movemask_epi8(result);

                // Verify the mask matches the required prefix length
                if ((mask & ((1 << chunkSize) - 1)) != ((1 << chunkSize) - 1)) {
                    match = false;
                    break;
                }
            }

            // Add index to results if there's a match
            if (match) {
                resultIndices.push_back(index);
            }
        }
    }

    return resultIndices;
}


std::vector<size_t> Dict::SIMDSearchFromEncodedFile(const std::string& str, const std::string& filename) const {
    std::vector<size_t> resultIndices;

    // Ensure the search string's length is <= 32 (AVX register size)
    size_t strLength = str.size();
    if (strLength > 32) {
        std::cerr << "Search string too long for SIMD search" << std::endl;
        return resultIndices;
    }

    // Prepare the search string for SIMD operations
    alignas(32) char strAligned[32] = {};
    std::copy(str.begin(), str.end(), strAligned);

    __m256i strVec = _mm256_load_si256(reinterpret_cast<const __m256i*>(strAligned));

    // Open the encoded file for reading
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening encoded file" << std::endl;
        return resultIndices;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Convert line to an index
        size_t index = std::stoull(line);

        // Check if the index exists in the datastore
        if (datastore.count(index)) {
            const std::string& word = datastore.at(index);

            // Only compare words that are at least as long as the search string
            if (word.size() >= strLength) {
                // Prepare the word's prefix for SIMD comparison
                alignas(32) char wordAligned[32] = {};
                std::copy(word.begin(), word.begin() + strLength, wordAligned);

                // Load the word's prefix into an AVX register
                __m256i wordVec = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wordAligned));

                // Perform SIMD comparison
                __m256i result = _mm256_cmpeq_epi8(wordVec, strVec);

                // Generate a bitmask from the comparison result
                int mask = _mm256_movemask_epi8(result);

                // Check if the first `strLength` bytes match
                int expectedMask = (1 << strLength) - 1;  // e.g., 0b111...1 (strLength bits)
                if ((mask & expectedMask) == expectedMask) {
                    resultIndices.push_back(index);
                }
            }
        }
    }

    file.close();
    return resultIndices;
}