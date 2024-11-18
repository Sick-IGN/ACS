#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <functional>
#include "Dict.h"

std::vector<size_t> vanillaSearch(const std::string& str, const std::string& filename) {
  std::ifstream file(filename);
  std::vector<size_t> indices;
  std::string line;
  size_t index = 0;

  if (!file.is_open()) {
    std::cerr << "error opening file" << std::endl;
    return indices;
  }

  while (std::getline(file, line)) {
    if (line == str) {
      indices.push_back(index);
    }
    ++index;
  }
  return indices;
}

std::vector<size_t> vanillaPrefixScan(const std::string& prefix, const std::string& filename) {
  std::ifstream file(filename);
  std::vector<size_t> indices;
  std::string line;
  size_t index = 0;

  if (!file.is_open()) {
    std::cerr << "error opening file" << std::endl;
    return indices;
  }

  while (std::getline(file, line)) {
    if (line.substr(0, prefix.size()) == prefix) {
      indices.push_back(index);
    }
    ++index;
  }
  return indices;
}

// Utility to time a function execution
void timeFunction(const std::string& operationName, std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << operationName << " took " << duration.count() << " seconds." << std::endl;
}

int main() {
    // Initialize the dictionary
    Dict dict;
    /*
    // 1. Load the dictionary
    std::cout << "Testing threadedLoad with 1 thread:" << std::endl;
    timeFunction("Time for threaded load (1 thread)", [&]() {
        dict.threadedLoad("column.txt", 1);  // Load the file using 1 thread
    });
    */  

    std::cout << "Testing threadedLoad with 8 threads:" << std::endl;
    timeFunction("Time for threaded load (8 threads)", [&]() {
        dict.threadedLoad("column.txt", 8);  // Load the file using 8 threads
    });
    std::cout << std::endl;

    std::cout << "Search for index in dict" << std::endl;
    timeFunction("Time for search", [&]() {
      dict.search("ypdizcglr");
    });

    std::cout << "Search for prefix scan in dict" << std::endl;
    timeFunction("Time for search", [&]() {
      dict.prefixSearch("yp");
    });
    std::cout << std::endl;

    // 2. Decode 'encoded.txt' into 'decoded.txt' (Test both single-threaded and 8 threads)
    std::cout << "Testing decodeFile operation..." << std::endl;
    std::cout << std::endl;

    std::cout << "Decoding encoded.txt with 1 thread:" << std::endl;
    timeFunction("Time for decodeFile (1 thread)", [&]() {
        dict.decodeFile("encoded.txt", "decoded.txt", 1);  // Decode 'encoded.txt' to 'decoded.txt' using 1 thread
    });

    std::cout << "Decoding encoded.txt with 8 threads:" << std::endl;
    timeFunction("Time for decodeFile (8 threads)", [&]() {
        dict.decodeFile("encoded.txt", "decoded.txt", 8);  // Decode 'encoded.txt' to 'decoded.txt' using 8 threads
    });
    std::cout << std::endl;

    // 3. Encode 'decoded.txt' into another file (Test both single-threaded and 8 threads)
    std::cout << "Encoding decoded.txt into encoded_again.txt with 1 thread:" << std::endl;
    timeFunction("Time for encodeFile (1 thread)", [&]() {
        dict.encodeFile("decoded.txt", "encoded_again.txt", 1);  // Encode 'decoded.txt' to 'encoded_again.txt' using 1 thread
    });

    std::cout << "Encoding decoded.txt into encoded_again.txt with 8 threads:" << std::endl;
    timeFunction("Time for encodeFile (8 threads)", [&]() {
        dict.encodeFile("decoded.txt", "encoded_again.txt", 8);  // Encode 'decoded.txt' to 'encoded_again.txt' using 8 threads
    });
    std::cout << std::endl;

    // 4. Search in 'decoded.txt' using vanilla search for 'ypdizcglr'
    std::cout << "Vanilla Search in 'decoded.txt' for 'ypdizcglr':" << std::endl;
    timeFunction("Vanilla Search (decoded.txt)", [&]() {
        auto indices = vanillaSearch("ypdizcglr", "decoded.txt");  // Search 'ypdizcglr' in 'decoded.txt'
        std::cout << "Found " << indices.size() << " matches." << std::endl;
    });

    // 5. Prefix Scan in 'decoded.txt' using vanilla prefix scan for 'or'
    std::cout << "Vanilla Prefix Scan in 'decoded.txt' for prefix 'or':" << std::endl;
    timeFunction("Vanilla Prefix Scan (decoded.txt)", [&]() {
        auto indices = vanillaPrefixScan("or", "decoded.txt");  // Prefix scan 'or' in 'decoded.txt'
        std::cout << "Found " << indices.size() << " matches." << std::endl;
    });
    std::cout << std::endl;

    // 6. Search in 'encoded.txt' using dict search for 'ypdizcglr' (both normal and SIMD)
    std::cout << "Dict Search in 'encoded.txt' for 'ypdizcglr' (normal):" << std::endl;
    timeFunction("Dict Search (normal) (encoded.txt)", [&]() {
        auto indices = dict.searchFromEncodedFile("ypdizcglr", "encoded.txt");  // Dict search (normal) in 'encoded.txt'
        std::cout << "Found " << indices.size() << " matches." << std::endl;
    });

    std::cout << "Dict Search in 'encoded.txt' for 'ypdizcglr' (SIMD):" << std::endl;
    timeFunction("Dict Search (SIMD) (encoded.txt)", [&]() {
        auto indices = dict.SIMDSearchFromEncodedFile("ypdizcglr", "encoded.txt");  // Dict search (SIMD) in 'encoded.txt'
        std::cout << "Found " << indices.size() << " matches." << std::endl;
    });

    std::cout << std::endl;
    // 7. Prefix Scan in 'encoded.txt' using dict prefix scan for 'or' (both normal and SIMD)
    std::cout << "Dict Prefix Scan in 'encoded.txt' for prefix 'or' (normal):" << std::endl;
    timeFunction("Dict Prefix Scan (normal) (encoded.txt)", [&]() {
        auto indices = dict.prefixSearchFromEncodedFile("or", "encoded.txt");  // Dict prefix scan (normal) in 'encoded.txt'
        std::cout << "Found " << indices.size() << " matches." << std::endl;
    });

    std::cout << "Dict Prefix Scan in 'encoded.txt' for prefix 'or' (SIMD):" << std::endl;
    timeFunction("Dict Prefix Scan (SIMD) (encoded.txt)", [&]() {
        auto indices = dict.SIMDPrefixSearchFromEncodedFile("or", "encoded.txt");  // Dict prefix scan (SIMD) in 'encoded.txt'
        std::cout << "Found " << indices.size() << " matches." << std::endl;
    });
    std::cout << std::endl;

    // 8. Generate Dict File (single-threaded and 8 threads)
    std::cout << "Testing genDictFile..." << std::endl;

    std::cout << "Generating dict file (single-threaded):" << std::endl;
    timeFunction("Time for genDictFile (single-threaded)", [&]() {
        dict.genDictFile("dict_file.txt");  // Generate dict file (single-threaded)
    });

    std::cout << "Generating dict file (8 threads):" << std::endl;
    timeFunction("Time for genDictFile (8 threads)", [&]() {
        dict.threadedGenFile("dict_file_threaded.txt", 8);  // Generate dict file (8 threads)
    });
    std::cout << std::endl;

    // 9. Generate pairs fror decoded.txt (single-threaded and 8 threads)
    std::cout << "Testing genPairs..." << std::endl;

    std::cout << "Generating pairs (single-threaded):" << std::endl;
    timeFunction("Time for genPairs (single-threaded)", [&]() {
        dict.genPairs("decoded.txt", "pairs_1_thread.txt", 1);  // Generate pairs from 'decoded.txt' using 1 thread
    });

    std::cout << "Generating pairs (8 threads):" << std::endl;
    timeFunction("Time for genPairs (8 threads)", [&]() {
        dict.genPairs("decoded.txt", "pairs_8_threads.txt", 8);  // Generate pairs from 'decoded.txt' using 8 threads
    });
    std::cout << std::endl;

    std::cout << "All operations completed." << std::endl;

    return 0;
}
