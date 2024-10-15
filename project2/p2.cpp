#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib> 
#include <random>
#include <immintrin.h>
#include <chrono>
#include <iomanip>
#include <fstream>

std::mt19937 generator(std::random_device{}());
#define TIME_POINT std::chrono::high_resolution_clock::now()
#define TIME_DURATION(start, end) std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()

// Function to generate an NxN sparse matrix with specified sparsity
int** generateMatrix(int N, float M) {
  // Allocate memory for the matrix using _mm_malloc
  int** matrix = (int**) _mm_malloc(N * sizeof(int*), 16); // Allocate row pointers with 16-byte alignment
  if (!matrix) {
    throw std::runtime_error("Failed to allocate memory for matrix rows.");
  }

  for (int i = 0; i < N; i++) {
    matrix[i] = (int*) _mm_malloc(N * sizeof(int), 16); // Allocate each row with 16-byte alignment
    if (!matrix[i]) {
      // If allocation fails, free previously allocated rows
      for (int j = 0; j < i; j++) {
        _mm_free(matrix[j]);
      }
      _mm_free(matrix);
      throw std::runtime_error("Failed to allocate memory for matrix row.");
    }
    std::fill(matrix[i], matrix[i] + N, 0); // Initialize all elements to 0
  }

  int totalElements = N * N;
  int nonZeroCount = static_cast<int>(totalElements * M); // Calculate number of non-zero elements

  // Ensure nonZeroCount does not exceed totalElements
  if (nonZeroCount > totalElements) {
    nonZeroCount = totalElements;
  }

  // Randomly set non-zero elements
  for (int count = 0; count < nonZeroCount;) {
    int row = generator() % N; // Random row index
    int col = generator() % N; // Random column index

    // Only set the element if it is still zero
    if (matrix[row][col] == 0) {
      matrix[row][col] = generator() % 10 + 1; // Assign a random value (1-10)
      count++;
    }
  }

  return matrix;
}

// Function to multiply a subset of rows for matrix multiplication
void multiplyPartial(int** m1, int** m2, int** out, int size, int startRow, int endRow) {
  for (int i = startRow; i < endRow; i++) {
    for (int j = 0; j < size; j++) {
        out[i][j] = 0;
        for (int k = 0; k < size; k++) {
      out[i][j] += m1[i][k] * m2[k][j];
        }
    }
  }
}

void threaded(int** m1, int** m2, int** out, int size, int threads) {

  int rowsPerThread = size / threads;
  int remainingRows = size % threads;

  std::vector<std::thread> threadPool;
  int currentRow = 0;

  for (int t = 0; t < threads; t++) {

    int startRow = currentRow;
    int endRow = startRow + rowsPerThread;
    if (remainingRows > 0) {
      endRow++;  
      remainingRows--;
    }
    currentRow = endRow;

    threadPool.push_back(std::thread(multiplyPartial, m1, m2, out, size, startRow, endRow));
  }

  for (std::thread &th : threadPool) {
    if (th.joinable()) {
        th.join();
    }
  }

}

// Helper function to print a matrix
void printMatrix(int** matrix, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
    }
  }
}

// Helper function to compare two matrices
bool compareMatrices(int** mat1, int** mat2, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (mat1[i][j] != mat2[i][j]) {
        return false;
      }
    }
  }
  return true;
}

void simdMultiplyPartial(int** m1, int** m2, int** out, int size, int startRow, int endRow) {
  for (int i = startRow; i < endRow; i++) {
    for (int j = 0; j < size; j += 4) { // Process 4 columns at a time
      __m128i sum = _mm_setzero_si128(); // Initialize the sum to zero
      for (int k = 0; k < size; k++) {
        __m128i a = _mm_set1_epi32(m1[i][k]);          // Broadcast m1[i][k] to all elements of the vector
        __m128i b = _mm_loadu_si128((__m128i*)&m2[k][j]); // Load 4 elements from m2[k][j] to m2[k][j+3]
        sum = _mm_add_epi32(sum, _mm_mullo_epi32(a, b)); // Multiply and accumulate
      }
      _mm_storeu_si128((__m128i*)&out[i][j], sum); // Store the sum in the output matrix
    }
  }
}

// Threaded SIMD matrix multiplication
void simdMatrixMultiply(int** m1, int** m2, int** out, int size, int threads) {

  int rowsPerThread = size / threads;
  int remainingRows = size % threads;

  std::vector<std::thread> threadPool;
  int currentRow = 0;

  for (int t = 0; t < threads; t++) {
    int startRow = currentRow;
    int endRow = startRow + rowsPerThread;

    if (remainingRows > 0) {
      endRow++;
      remainingRows--;
    }
    currentRow = endRow;

    // Launch a thread for each subset of rows
    threadPool.push_back(std::thread(simdMultiplyPartial, m1, m2, out, size, startRow, endRow));
  }

  // Join all threads
  for (std::thread &th : threadPool) {
    if (th.joinable()) {
      th.join();
    }
  }
}

void multiplyBlock(int** m1, int** m2, int** out, int size, int blockSize, int startRow, int endRow) {
  for (int ii = startRow; ii < endRow; ii++) {
    for (int jj = 0; jj < size; jj++) {
      int sum = 0;
      for (int kk = 0; kk < size; kk++) {
        sum += m1[ii][kk] * m2[kk][jj];
      }
      out[ii][jj] += sum; // Accumulate results in the output matrix
    }
  }
}

void unoptimized(int** m1, int** m2, int** out, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
        out[i][j] = 0;
        for (int k = 0; k < size; k++) {
          out[i][j] += m1[i][k] * m2[k][j];
        }
    }
  }
}

void cacheMultiply(int** m1, int** m2, int** out, int size, int blockSize, int threads) {

  std::vector<std::thread> threadPool;

  // Determine the number of rows each thread will process
  int rowsPerThread = size / threads;
  int remainingRows = size % threads;

  for (int t = 0; t < threads; ++t) {
    int startRow = t * rowsPerThread;
    int endRow = (t + 1) * rowsPerThread;

    if (t == threads - 1) {
      endRow += remainingRows; // Last thread takes the remaining rows
    }

    // Create a thread to multiply the assigned rows
    threadPool.emplace_back([=]() {
      for (int ii = startRow; ii < endRow; ii += blockSize) {
        for (int jj = 0; jj < size; jj += blockSize) {
          for (int kk = 0; kk < size; kk += blockSize) {
            // Multiply blocks
            for (int i = ii; i < std::min(ii + blockSize, endRow); i++) {
              for (int j = jj; j < std::min(jj + blockSize, size); j++) {
                int sum = 0;
                for (int k = kk; k < std::min(kk + blockSize, size); k++) {
                  sum += m1[i][k] * m2[k][j];
                }
                out[i][j] += sum; // Accumulate the result
              }
            }
          }
        }
      }
    });
  }

  // Join threads
  for (auto& thread : threadPool) {
    thread.join();
  }
}

void simdMultiplyBlock(int** m1, int** m2, int** out, int size, int blockSize, int startRow, int endRow) {
  for (int ii = startRow; ii < endRow; ii += blockSize) {
    for (int jj = 0; jj < size; jj += blockSize) {
      for (int kk = 0; kk < size; kk += blockSize) {

        // Multiply blocks using SIMD
        for (int i = ii; i < std::min(ii + blockSize, endRow); i++) {
          for (int j = jj; j < std::min(jj + blockSize, size); j += 4) {  // Process 4 columns at a time
            __m128i sum = _mm_setzero_si128();  // Initialize SIMD register to zero
            for (int k = kk; k < std::min(kk + blockSize, size); k++) {
              __m128i a = _mm_set1_epi32(m1[i][k]);  // Broadcast m1[i][k] to all elements of SIMD vector
              __m128i b = _mm_loadu_si128((__m128i*)&m2[k][j]);  // Load 4 elements from m2[k][j] to m2[k][j+3]
              sum = _mm_add_epi32(sum, _mm_mullo_epi32(a, b));  // Multiply and accumulate
            }
            // Accumulate the result into the output matrix
            __m128i outVec = _mm_loadu_si128((__m128i*)&out[i][j]);
            outVec = _mm_add_epi32(outVec, sum);
            _mm_storeu_si128((__m128i*)&out[i][j], outVec);  // Store the result back into out[i][j:j+3]
          }
        }

      }
    }
  }
}

// Threaded SIMD matrix multiplication with blocking
void cacheSIMD(int** m1, int** m2, int** out, int size, int blockSize, int threads) {

  std::vector<std::thread> threadPool;

  // Determine the number of rows each thread will process
  int rowsPerThread = size / threads;
  int remainingRows = size % threads;

  for (int t = 0; t < threads; ++t) {
    int startRow = t * rowsPerThread;
    int endRow = (t + 1) * rowsPerThread;

    if (t == threads - 1) {
      endRow += remainingRows;  // Last thread takes the remaining rows
    }

    // Create a thread to multiply the assigned rows using SIMD and blocking
    threadPool.emplace_back([=]() {
      simdMultiplyBlock(m1, m2, out, size, blockSize, startRow, endRow);
    });
  }

  // Join all threads
  for (auto& thread : threadPool) {
    thread.join();
  }
}

void runTest(int size, float sparsity) {
  int** m1 = generateMatrix(size, sparsity);
  int** m2 = generateMatrix(size, sparsity);

  int** outNative = generateMatrix(size, 0);

  // Output initializations for different thread counts and block sizes
  int** out1Thread = generateMatrix(size, 0);
  int** out4Thread = generateMatrix(size, 0);
  int** out8Thread = generateMatrix(size, 0);
  int** out16Thread = generateMatrix(size, 0);

  int** out1ThreadSIMD = generateMatrix(size, 0);
  int** out4ThreadSIMD = generateMatrix(size, 0);
  int** out8ThreadSIMD = generateMatrix(size, 0);
  int** out16ThreadSIMD = generateMatrix(size, 0);

  // Cache optimizations with block sizes 4, 64, 256
  int** out1ThreadCache4 = generateMatrix(size, 0);
  int** out4ThreadCache4 = generateMatrix(size, 0);
  int** out8ThreadCache4 = generateMatrix(size, 0);
  int** out16ThreadCache4 = generateMatrix(size, 0);

  int** out1ThreadCache64 = generateMatrix(size, 0);
  int** out4ThreadCache64 = generateMatrix(size, 0);
  int** out8ThreadCache64 = generateMatrix(size, 0);
  int** out16ThreadCache64 = generateMatrix(size, 0);

  int** out1ThreadCache256 = generateMatrix(size, 0);
  int** out4ThreadCache256 = generateMatrix(size, 0);
  int** out8ThreadCache256 = generateMatrix(size, 0);
  int** out16ThreadCache256 = generateMatrix(size, 0);

  // SIMD + Cache optimizations with block sizes 4, 64, 256
  int** out1ThreadAll4 = generateMatrix(size, 0);
  int** out4ThreadAll4 = generateMatrix(size, 0);
  int** out8ThreadAll4 = generateMatrix(size, 0);
  int** out16ThreadAll4 = generateMatrix(size, 0);

  int** out1ThreadAll64 = generateMatrix(size, 0);
  int** out4ThreadAll64 = generateMatrix(size, 0);
  int** out8ThreadAll64 = generateMatrix(size, 0);
  int** out16ThreadAll64 = generateMatrix(size, 0);

  int** out1ThreadAll256 = generateMatrix(size, 0);
  int** out4ThreadAll256 = generateMatrix(size, 0);
  int** out8ThreadAll256 = generateMatrix(size, 0);
  int** out16ThreadAll256 = generateMatrix(size, 0);

  // Timing each method and printing results
  auto start = std::chrono::high_resolution_clock::now();
  unoptimized(m1, m2, outNative, size);
  auto end = std::chrono::high_resolution_clock::now();
  auto nativeTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Threaded
  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out1Thread, size, 1);
  end = std::chrono::high_resolution_clock::now();
  auto t1Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out4Thread, size, 4);
  end = std::chrono::high_resolution_clock::now();
  auto t4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out8Thread, size, 8);
  end = std::chrono::high_resolution_clock::now();
  auto t8Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out16Thread, size, 16);
  end = std::chrono::high_resolution_clock::now();
  auto t16Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // SIMD
  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out1ThreadSIMD, size, 1);
  end = std::chrono::high_resolution_clock::now();
  auto simd1Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out4ThreadSIMD, size, 4);
  end = std::chrono::high_resolution_clock::now();
  auto simd4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out8ThreadSIMD, size, 8);
  end = std::chrono::high_resolution_clock::now();
  auto simd8Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out16ThreadSIMD, size, 16);
  end = std::chrono::high_resolution_clock::now();
  auto simd16Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Cache optimizations with block size 4
  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out1ThreadCache4, size, 4, 1);
  end = std::chrono::high_resolution_clock::now();
  auto cache1_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out4ThreadCache4, size, 4, 4);
  end = std::chrono::high_resolution_clock::now();
  auto cache4_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out8ThreadCache4, size, 4, 8);
  end = std::chrono::high_resolution_clock::now();
  auto cache8_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out16ThreadCache4, size, 4, 16);
  end = std::chrono::high_resolution_clock::now();
  auto cache16_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Repeat for Cache with block size 64 and 256
  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out1ThreadCache64, size, 64, 1);
  end = std::chrono::high_resolution_clock::now();
  auto cache1_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out4ThreadCache64, size, 64, 4);
  end = std::chrono::high_resolution_clock::now();
  auto cache4_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out8ThreadCache64, size, 64, 8);
  end = std::chrono::high_resolution_clock::now();
  auto cache8_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out16ThreadCache64, size, 64, 16);
  end = std::chrono::high_resolution_clock::now();
  auto cache16_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out1ThreadCache256, size, 256, 1);
  end = std::chrono::high_resolution_clock::now();
  auto cache1_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out4ThreadCache256, size, 256, 4);
  end = std::chrono::high_resolution_clock::now();
  auto cache4_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out8ThreadCache256, size, 256, 8);
  end = std::chrono::high_resolution_clock::now();
  auto cache8_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out16ThreadCache256, size, 256, 16);
  end = std::chrono::high_resolution_clock::now();
  auto cache16_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Final All optimizations
  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 1);
  end = std::chrono::high_resolution_clock::now();
  auto all1_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 4);
  end = std::chrono::high_resolution_clock::now();
  auto all4_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 8);
  end = std::chrono::high_resolution_clock::now();
  auto all8_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 16);
  end = std::chrono::high_resolution_clock::now();
  auto all16_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Final All optimizations 64 block
  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 64, 1);
  end = std::chrono::high_resolution_clock::now();
  auto all1_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 64, 4);
  end = std::chrono::high_resolution_clock::now();
  auto all4_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 64, 8);
  end = std::chrono::high_resolution_clock::now();
  auto all8_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 64, 16);
  end = std::chrono::high_resolution_clock::now();
  auto all16_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Final All optimizations 256 block
  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 1);
  end = std::chrono::high_resolution_clock::now();
  auto all1_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 4);
  end = std::chrono::high_resolution_clock::now();
  auto all4_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 8);
  end = std::chrono::high_resolution_clock::now();
  auto all8_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 16);
  end = std::chrono::high_resolution_clock::now();
  auto all16_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  std::ofstream outFile("results1.md", std::ios::app);
  if (!outFile) {
      std::cerr << "Error opening file!" << std::endl;
      return; // Handle error
  }

  // Output the formatted table with results for all runs
  outFile << "\n## Size: " << size << "x" << size << " ------ " << "Sparsity: " << sparsity << '\n';
  outFile << "| Method                               | Time (ns) |\n";
  outFile << "|--------------------------------------|-----------|\n";
  outFile << "| Unoptimized                          | " << nativeTime << " |\n";
  outFile << "| Threaded (1 thread)                  | " << t1Time << " |\n";
  outFile << "| Threaded (4 threads)                 | " << t4Time << " |\n";
  outFile << "| Threaded (8 threads)                 | " << t8Time << " |\n";
  outFile << "| Threaded (16 threads)                | " << t16Time << " |\n";
  outFile << "| SIMD (1 thread)                      | " << simd1Time << " |\n";
  outFile << "| SIMD (4 threads)                     | " << simd4Time << " |\n";
  outFile << "| SIMD (8 threads)                     | " << simd8Time << " |\n";
  outFile << "| SIMD (16 threads)                    | " << simd16Time << " |\n";
  outFile << "| Cache (block 4, 1 thread)            | " << cache1_4Time << " |\n";
  outFile << "| Cache (block 4, 4 threads)           | " << cache4_4Time << " |\n";
  outFile << "| Cache (block 4, 8 threads)           | " << cache8_4Time << " |\n";
  outFile << "| Cache (block 4, 16 threads)          | " << cache16_4Time << " |\n";
  outFile << "| Cache (block 64, 1 thread)           | " << cache1_64Time << " |\n";
  outFile << "| Cache (block 64, 4 threads)          | " << cache4_64Time << " |\n";
  outFile << "| Cache (block 64, 8 threads)          | " << cache8_64Time << " |\n";
  outFile << "| Cache (block 64, 16 threads)         | " << cache16_64Time << " |\n";
  outFile << "| Cache (block 256, 1 thread)          | " << cache1_256Time << " |\n";
  outFile << "| Cache (block 256, 4 threads)         | " << cache4_256Time << " |\n";
  outFile << "| Cache (block 256, 8 threads)         | " << cache8_256Time << " |\n";
  outFile << "| Cache (block 256, 16 threads)        | " << cache16_256Time << " |\n";
  outFile << "| All opt (block 4, 1 thread)          | " << all1_4Time << " |\n";
  outFile << "| All opt (block 4, 4 threads)         | " << all4_4Time << " |\n";
  outFile << "| All opt (block 4, 8 threads)         | " << all8_4Time << " |\n";
  outFile << "| All opt (block 4, 16 threads)        | " << all16_4Time << " |\n";
  outFile << "| All opt (block 64, 1 thread)         | " << all1_64Time << " |\n";
  outFile << "| All opt (block 64, 4 threads)        | " << all4_64Time << " |\n";
  outFile << "| All opt (block 64, 8 threads)        | " << all8_64Time << " |\n";
  outFile << "| All opt (block 64, 16 threads)       | " << all16_64Time << " |\n";
  outFile << "| All opt (block 256, 1 thread)        | " << all1_256Time << " |\n";
  outFile << "| All opt (block 256, 4 threads)       | " << all4_256Time << " |\n";
  outFile << "| All opt (block 256, 8 threads)       | " << all8_256Time << " |\n";
  outFile << "| All opt (block 256, 16 threads)      | " << all16_256Time << " |\n";
}

//smaller test set for larger size arrays
void limitedTest(int size, float sparsity) {
  int** m1 = generateMatrix(size, sparsity);
  int** m2 = generateMatrix(size, sparsity);

  int** outNative = generateMatrix(size, 0);

  // Output initializations for different thread counts and block sizes
  int** out1Thread = generateMatrix(size, 0);
  int** out8Thread = generateMatrix(size, 0);

  int** out1ThreadSIMD = generateMatrix(size, 0);
  int** out8ThreadSIMD = generateMatrix(size, 0);

  // Cache optimizations with block sizes 4, 64, 256
  int** out1ThreadCache4 = generateMatrix(size, 0);
  int** out8ThreadCache4 = generateMatrix(size, 0);

  int** out1ThreadCache256 = generateMatrix(size, 0);
  int** out8ThreadCache256 = generateMatrix(size, 0);

  // SIMD + Cache optimizations with block sizes 4, 64, 256
  int** out1ThreadAll4 = generateMatrix(size, 0);
  int** out8ThreadAll4 = generateMatrix(size, 0);

  int** out1ThreadAll256 = generateMatrix(size, 0);
  int** out8ThreadAll256 = generateMatrix(size, 0);
  // Timing each method and printing results
  auto start = std::chrono::high_resolution_clock::now();
  unoptimized(m1, m2, outNative, size);
  auto end = std::chrono::high_resolution_clock::now();
  auto nativeTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 1 << std::endl;
  // Threaded
  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out1Thread, size, 1);
  end = std::chrono::high_resolution_clock::now();
  auto t1Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 2 << std::endl;

  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out8Thread, size, 8);
  end = std::chrono::high_resolution_clock::now();
  auto t8Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 3 << std::endl;
  // SIMD
  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out1ThreadSIMD, size, 1);
  end = std::chrono::high_resolution_clock::now();
  auto simd1Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 4 << std::endl;

  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out8ThreadSIMD, size, 8);
  end = std::chrono::high_resolution_clock::now();
  auto simd8Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 5 << std::endl;

  // Cache optimizations with block size 4
  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out1ThreadCache4, size, 4, 1);
  end = std::chrono::high_resolution_clock::now();
  auto cache1_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 6 << std::endl;

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out8ThreadCache4, size, 4, 8);
  end = std::chrono::high_resolution_clock::now();
  auto cache8_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 7 << std::endl;

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out1ThreadCache256, size, 256, 1);
  end = std::chrono::high_resolution_clock::now();
  auto cache1_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 8 << std::endl;

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out8ThreadCache256, size, 256, 8);
  end = std::chrono::high_resolution_clock::now();
  auto cache8_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 9 << std::endl;

  // Final All optimizations
  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 1);
  end = std::chrono::high_resolution_clock::now();
  auto all1_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 10 << std::endl;

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 8);
  end = std::chrono::high_resolution_clock::now();
  auto all8_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 11 << std::endl;

  // Final All optimizations 256 block
  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 1);
  end = std::chrono::high_resolution_clock::now();
  auto all1_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 12 << std::endl;

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 8);
  end = std::chrono::high_resolution_clock::now();
  auto all8_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << 13 << std::endl;

  std::ofstream outFile("results_exe.md", std::ios::app);
  if (!outFile) {
      std::cerr << "Error opening file!" << std::endl;
      return; // Handle error
  }

  // Output the formatted table with results for all runs
  outFile << "\n## Size: " << size << "x" << size << " ------ " << "Sparsity: " << sparsity << '\n';
  outFile << "| Method                               | Time (ns) |\n";
  outFile << "|--------------------------------------|-----------|\n";
  outFile << "| Unoptimized                          | " << nativeTime << " |\n";
  outFile << "| Threaded (1 thread)                  | " << t1Time << " |\n";
  outFile << "| Threaded (8 threads)                 | " << t8Time << " |\n";
  outFile << "| SIMD (1 thread)                      | " << simd1Time << " |\n";
  outFile << "| SIMD (8 threads)                     | " << simd8Time << " |\n";
  outFile << "| Cache (block 4, 1 thread)            | " << cache1_4Time << " |\n";
  outFile << "| Cache (block 4, 8 threads)           | " << cache8_4Time << " |\n";
  outFile << "| Cache (block 256, 1 thread)          | " << cache1_256Time << " |\n";
  outFile << "| Cache (block 256, 8 threads)         | " << cache8_256Time << " |\n";
  outFile << "| All opt (block 4, 1 thread)          | " << all1_4Time << " |\n";
  outFile << "| All opt (block 4, 8 threads)         | " << all8_4Time << " |\n";
  outFile << "| All opt (block 256, 1 thread)        | " << all1_256Time << " |\n";
  outFile << "| All opt (block 256, 8 threads)       | " << all8_256Time << " |\n";
}

void variedSparsityTest(int size, float s1, float s2) {
  int** m1 = generateMatrix(size, s1);
  int** m2 = generateMatrix(size, s2);
  int** outNative = generateMatrix(size, 0);

  // Output initializations for different thread counts and block sizes
  int** out1Thread = generateMatrix(size, 0);
  int** out4Thread = generateMatrix(size, 0);
  int** out8Thread = generateMatrix(size, 0);
  int** out16Thread = generateMatrix(size, 0);

  int** out1ThreadSIMD = generateMatrix(size, 0);
  int** out4ThreadSIMD = generateMatrix(size, 0);
  int** out8ThreadSIMD = generateMatrix(size, 0);
  int** out16ThreadSIMD = generateMatrix(size, 0);

  // Cache optimizations with block sizes 4, 64, 256
  int** out1ThreadCache4 = generateMatrix(size, 0);
  int** out4ThreadCache4 = generateMatrix(size, 0);
  int** out8ThreadCache4 = generateMatrix(size, 0);
  int** out16ThreadCache4 = generateMatrix(size, 0);

  int** out1ThreadCache64 = generateMatrix(size, 0);
  int** out4ThreadCache64 = generateMatrix(size, 0);
  int** out8ThreadCache64 = generateMatrix(size, 0);
  int** out16ThreadCache64 = generateMatrix(size, 0);

  int** out1ThreadCache256 = generateMatrix(size, 0);
  int** out4ThreadCache256 = generateMatrix(size, 0);
  int** out8ThreadCache256 = generateMatrix(size, 0);
  int** out16ThreadCache256 = generateMatrix(size, 0);

  // SIMD + Cache optimizations with block sizes 4, 64, 256
  int** out1ThreadAll4 = generateMatrix(size, 0);
  int** out4ThreadAll4 = generateMatrix(size, 0);
  int** out8ThreadAll4 = generateMatrix(size, 0);
  int** out16ThreadAll4 = generateMatrix(size, 0);

  int** out1ThreadAll64 = generateMatrix(size, 0);
  int** out4ThreadAll64 = generateMatrix(size, 0);
  int** out8ThreadAll64 = generateMatrix(size, 0);
  int** out16ThreadAll64 = generateMatrix(size, 0);

  int** out1ThreadAll256 = generateMatrix(size, 0);
  int** out4ThreadAll256 = generateMatrix(size, 0);
  int** out8ThreadAll256 = generateMatrix(size, 0);
  int** out16ThreadAll256 = generateMatrix(size, 0);

  // Timing each method and printing results
  auto start = std::chrono::high_resolution_clock::now();
  unoptimized(m1, m2, outNative, size);
  auto end = std::chrono::high_resolution_clock::now();
  auto nativeTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Threaded
  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out1Thread, size, 1);
  end = std::chrono::high_resolution_clock::now();
  auto t1Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out4Thread, size, 4);
  end = std::chrono::high_resolution_clock::now();
  auto t4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out8Thread, size, 8);
  end = std::chrono::high_resolution_clock::now();
  auto t8Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  threaded(m1, m2, out16Thread, size, 16);
  end = std::chrono::high_resolution_clock::now();
  auto t16Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // SIMD
  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out1ThreadSIMD, size, 1);
  end = std::chrono::high_resolution_clock::now();
  auto simd1Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out4ThreadSIMD, size, 4);
  end = std::chrono::high_resolution_clock::now();
  auto simd4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out8ThreadSIMD, size, 8);
  end = std::chrono::high_resolution_clock::now();
  auto simd8Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  simdMatrixMultiply(m1, m2, out16ThreadSIMD, size, 16);
  end = std::chrono::high_resolution_clock::now();
  auto simd16Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Cache optimizations with block size 4
  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out1ThreadCache4, size, 4, 1);
  end = std::chrono::high_resolution_clock::now();
  auto cache1_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out4ThreadCache4, size, 4, 4);
  end = std::chrono::high_resolution_clock::now();
  auto cache4_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out8ThreadCache4, size, 4, 8);
  end = std::chrono::high_resolution_clock::now();
  auto cache8_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out16ThreadCache4, size, 4, 16);
  end = std::chrono::high_resolution_clock::now();
  auto cache16_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Repeat for Cache with block size 64 and 256
  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out1ThreadCache64, size, 64, 1);
  end = std::chrono::high_resolution_clock::now();
  auto cache1_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out4ThreadCache64, size, 64, 4);
  end = std::chrono::high_resolution_clock::now();
  auto cache4_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out8ThreadCache64, size, 64, 8);
  end = std::chrono::high_resolution_clock::now();
  auto cache8_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out16ThreadCache64, size, 64, 16);
  end = std::chrono::high_resolution_clock::now();
  auto cache16_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out1ThreadCache256, size, 256, 1);
  end = std::chrono::high_resolution_clock::now();
  auto cache1_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out4ThreadCache256, size, 256, 4);
  end = std::chrono::high_resolution_clock::now();
  auto cache4_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out8ThreadCache256, size, 256, 8);
  end = std::chrono::high_resolution_clock::now();
  auto cache8_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheMultiply(m1, m2, out16ThreadCache256, size, 256, 16);
  end = std::chrono::high_resolution_clock::now();
  auto cache16_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Final All optimizations
  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 1);
  end = std::chrono::high_resolution_clock::now();
  auto all1_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 4);
  end = std::chrono::high_resolution_clock::now();
  auto all4_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 8);
  end = std::chrono::high_resolution_clock::now();
  auto all8_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 4, 16);
  end = std::chrono::high_resolution_clock::now();
  auto all16_4Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Final All optimizations 64 block
  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 64, 1);
  end = std::chrono::high_resolution_clock::now();
  auto all1_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 64, 4);
  end = std::chrono::high_resolution_clock::now();
  auto all4_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 64, 8);
  end = std::chrono::high_resolution_clock::now();
  auto all8_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 64, 16);
  end = std::chrono::high_resolution_clock::now();
  auto all16_64Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  // Final All optimizations 256 block
  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 1);
  end = std::chrono::high_resolution_clock::now();
  auto all1_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 4);
  end = std::chrono::high_resolution_clock::now();
  auto all4_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 8);
  end = std::chrono::high_resolution_clock::now();
  auto all8_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  cacheSIMD(m1, m2, out1ThreadAll4, size, 256, 16);
  end = std::chrono::high_resolution_clock::now();
  auto all16_256Time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  std::ofstream outFile("results_varied.md", std::ios::app);
  if (!outFile) {
      std::cerr << "Error opening file!" << std::endl;
      return; // Handle error
  }

  // Output the formatted table with results for all runs
  outFile << "\n## Size: " << size << "x" << size << " ------ " << "Sparsity: " << s1 << " * " << s2 << '\n';
  outFile << "| Method                               | Time (ns) |\n";
  outFile << "|--------------------------------------|-----------|\n";
  outFile << "| Unoptimized                          | " << nativeTime << " |\n";
  outFile << "| Threaded (1 thread)                  | " << t1Time << " |\n";
  outFile << "| Threaded (4 threads)                 | " << t4Time << " |\n";
  outFile << "| Threaded (8 threads)                 | " << t8Time << " |\n";
  outFile << "| Threaded (16 threads)                | " << t16Time << " |\n";
  outFile << "| SIMD (1 thread)                      | " << simd1Time << " |\n";
  outFile << "| SIMD (4 threads)                     | " << simd4Time << " |\n";
  outFile << "| SIMD (8 threads)                     | " << simd8Time << " |\n";
  outFile << "| SIMD (16 threads)                    | " << simd16Time << " |\n";
  outFile << "| Cache (block 4, 1 thread)            | " << cache1_4Time << " |\n";
  outFile << "| Cache (block 4, 4 threads)           | " << cache4_4Time << " |\n";
  outFile << "| Cache (block 4, 8 threads)           | " << cache8_4Time << " |\n";
  outFile << "| Cache (block 4, 16 threads)          | " << cache16_4Time << " |\n";
  outFile << "| Cache (block 64, 1 thread)           | " << cache1_64Time << " |\n";
  outFile << "| Cache (block 64, 4 threads)          | " << cache4_64Time << " |\n";
  outFile << "| Cache (block 64, 8 threads)          | " << cache8_64Time << " |\n";
  outFile << "| Cache (block 64, 16 threads)         | " << cache16_64Time << " |\n";
  outFile << "| Cache (block 256, 1 thread)          | " << cache1_256Time << " |\n";
  outFile << "| Cache (block 256, 4 threads)         | " << cache4_256Time << " |\n";
  outFile << "| Cache (block 256, 8 threads)         | " << cache8_256Time << " |\n";
  outFile << "| Cache (block 256, 16 threads)        | " << cache16_256Time << " |\n";
  outFile << "| All opt (block 4, 1 thread)          | " << all1_4Time << " |\n";
  outFile << "| All opt (block 4, 4 threads)         | " << all4_4Time << " |\n";
  outFile << "| All opt (block 4, 8 threads)         | " << all8_4Time << " |\n";
  outFile << "| All opt (block 4, 16 threads)        | " << all16_4Time << " |\n";
  outFile << "| All opt (block 64, 1 thread)         | " << all1_64Time << " |\n";
  outFile << "| All opt (block 64, 4 threads)        | " << all4_64Time << " |\n";
  outFile << "| All opt (block 64, 8 threads)        | " << all8_64Time << " |\n";
  outFile << "| All opt (block 64, 16 threads)       | " << all16_64Time << " |\n";
  outFile << "| All opt (block 256, 1 thread)        | " << all1_256Time << " |\n";
  outFile << "| All opt (block 256, 4 threads)       | " << all4_256Time << " |\n";
  outFile << "| All opt (block 256, 8 threads)       | " << all8_256Time << " |\n";
  outFile << "| All opt (block 256, 16 threads)      | " << all16_256Time << " |\n";
}

int main() {
  /*
  runTest(10, 0.001); //0.1%
  runTest(10, 0.01);  //1%
  runTest(10, 0.1);   //10%
  runTest(10, 0.5);   //50%
  runTest(10, 1);     //100%

  runTest(100, 0.001); //0.1%
  runTest(100, 0.01);  //1%
  runTest(100, 0.1);   //10%
  runTest(100, 0.5);   //50%
  runTest(100, 1);     //100%

  runTest(500, 0.001); //0.1%
  runTest(500, 0.01);  //1%
  runTest(500, 0.1);   //10%
  runTest(500, 0.5);   //50%
  runTest(500, 1);     //100%
  
  runTest(1000, 0.001); //0.1%
  runTest(1000, 0.01);  //1%
  runTest(1000, 0.1);   //10%
  runTest(1000, 0.5);   //50%
  runTest(1000, 1);     //100%
  
  limitedTest(5000, 0.001); //0.1%
  limitedTest(5000, 0.01);  //1%
  limitedTest(5000, 0.1);   //10%
  runTest(5000, 0.5);   //50%
  limitedTest(5000, 1);     //100%
  
  */
  variedSparsityTest(1000, 0.01, 1);
  variedSparsityTest(1000, 0.05, 0.5);
  variedSparsityTest(1000, 0.1, 0.9);
  /*
  variedSparsityTest(1500, 0.01, 1);
  variedSparsityTest(1500, 0.05, 0.5);
  variedSparsityTest(1500, 0.1, 0.9);

  variedSparsityTest(500, 0.01, 1);
  variedSparsityTest(500, 0.05, 0.5);
  variedSparsityTest(500, 0.1, 0.9);
  */

  //runTest(1500, 0.001);
  //runTest(1500, 1);
  return 0;
}