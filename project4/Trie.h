#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <immintrin.h>
#include <string>
#include <thread>
#include <mutex>
#include <functional>

struct TrieNode {

  TrieNode* children[26];  //for a-z
  int index; //-1 by default, else word index

  TrieNode();

};

class Trie {

  private:
    TrieNode* root; //root ptr
    int cnt; //cnt of unique vals

  public:
    
    Trie();

    ~Trie();
    void deleteNode(TrieNode* node);

    size_t insert(const std::string& word);

    size_t search(const std::string&) const;
    size_t SIMDSearch(const std::string&) const;

    std::vector<size_t> prefixSearch(const std::string& prefix) const;
    std::vector<size_t> SIMDPrefixSearch(const std::string& prefix) const;

    void insertBatch(std::vector<std::string>& words, std::mutex& mtx);
    void readChunk(std::ifstream& file, long start, long end, std::vector<std::string>& chunk);

    void loadFromFile(const std::string& filename);   
    void threadedLoad(const std::string& filename, int numThreads); 

    void printTrie() const;
    void printTrieHelper(TrieNode* node, std::string& currentWord) const;

    void collectWords(TrieNode* node, std::vector<size_t>& result) const;
};

#endif