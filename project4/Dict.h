#ifndef DICT_H
#define DICT_H

#include "Trie.h"
#include <vector>
#include <unordered_map>
#include <mutex>
#include <fstream>
#include <iostream>
#include <thread>
#include <immintrin.h>
#include <cstring>

class Dict {
  
  private:
    Trie* trie;
    std::unordered_map<size_t, std::string> datastore;

    void insertBatch(std::vector<std::string>& words, std::mutex& mtx);
    void readChunk(std::ifstream& file, long start, long end, std::vector<std::string>& chunk);

  public:

    Dict();
    ~Dict();

    void loadFromFile(const std::string& filename);
    void threadedLoad(const std::string& filename, int numThreads); 

    size_t search(const std::string& str) const;
    std::vector<size_t> searchFromEncodedFile(const std::string& str, const std::string& filename) const;
    std::vector<size_t> SIMDSearchFromEncodedFile(const std::string& str, const std::string& filename) const;

    std::vector<size_t> prefixSearch(const std::string& prefix) const;
    std::vector<size_t> prefixSearchFromEncodedFile(const std::string& str, const std::string& filename) const;
    std::vector<size_t> SIMDPrefixSearchFromEncodedFile(const std::string& prefix, const std::string& filename) const;

    std::string returnString(const size_t index) const;

    void genDictFile(const std::string& filename) const;

    void threadedGenFile(const std::string& filename, const size_t numThreads) const;
    void writeChunk(const std::unordered_map<size_t, std::string>& chunk, std::ofstream& outFile) const;

    void encodeFile(const std::string& inFile, const std::string& outFile, const size_t numThreads) const;
    void decodeFile(const std::string& inFile, const std::string& outFile, const size_t numThreads) const;

    void genPairs(const std::string& inFile, const std::string& outFile, const size_t numThreads) const;
    void processChunk(const std::string& inFile, size_t start, size_t end, std::ofstream& outputFile, std::mutex& mtx) const;
};

#endif