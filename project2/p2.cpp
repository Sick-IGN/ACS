#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <immintrin.h>
#include <memory>
#include <atomic>
#include <cstring>
#include <omp.h>
#include <algorithm>
#include <mutex>
#include <fstream>

struct CSRMatrix {
    std::vector<int> values;
    std::vector<int> colIndex;
    std::vector<int> rowIndex;
};

std::vector<std::vector<int>> generateMatrix(int size, double sparsity) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    int totalElements = size * size;
    int nonZeroElements = static_cast<int>(totalElements * sparsity);

    std::srand(std::time(0)); // Seed for random number generation

    for (int i = 0; i < nonZeroElements; ++i) {
        int row = std::rand() % size;
        int col = std::rand() % size;
        while (matrix[row][col] != 0) {
            row = std::rand() % size;
            col = std::rand() % size;
        }
        matrix[row][col] = std::rand() % 10 + 1; // Assign a random value between 1 and 10
    }

    return matrix;
}

CSRMatrix convertToCSR(const std::vector<std::vector<int>>& matrix) {
    CSRMatrix csr;
    int size = matrix.size();
    
    csr.rowIndex.push_back(0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] != 0) {
                csr.values.push_back(matrix[i][j]);
                csr.colIndex.push_back(j);
            }
        }
        csr.rowIndex.push_back(csr.values.size());
    }
    return csr;
}

std::vector<std::vector<int>> convertToDense(const CSRMatrix& csr, int size) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = csr.rowIndex[i]; j < csr.rowIndex[i + 1]; ++j) {
            matrix[i][csr.colIndex[j]] = csr.values[j];
        }
    }
    return matrix;
}

bool compareDenseDense(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        return false;
    }
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[0].size(); ++j) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool compareCSRCSR(const CSRMatrix& A, const CSRMatrix& B) {
    return (A.values == B.values) && (A.colIndex == B.colIndex) && (A.rowIndex == B.rowIndex);
}

bool compareDenseCSR(const std::vector<std::vector<int>>& dense, const CSRMatrix& csr) {
    int size = dense.size();
    std::vector<std::vector<int>> denseFromCSR(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = csr.rowIndex[i]; j < csr.rowIndex[i + 1]; ++j) {
            denseFromCSR[i][csr.colIndex[j]] = csr.values[j];
        }
    }

    return compareDenseDense(dense, denseFromCSR);
}

std::vector<std::vector<int>> multiplyDenseDense(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int size = A.size();
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

CSRMatrix multiplyCSRCSR(const CSRMatrix& A, const CSRMatrix& B, int size) {
    CSRMatrix C;
    std::vector<int> temp(size, 0);
    std::vector<bool> marker(size, false);

    C.rowIndex.push_back(0);
    for (int i = 0; i < size; ++i) {
        for (int j = A.rowIndex[i]; j < A.rowIndex[i + 1]; ++j) {
            int colA = A.colIndex[j];
            int valA = A.values[j];
            for (int k = B.rowIndex[colA]; k < B.rowIndex[colA + 1]; ++k) {
                int colB = B.colIndex[k];
                int valB = B.values[k];
                if (!marker[colB]) {
                    marker[colB] = true;
                    C.colIndex.push_back(colB);
                }
                temp[colB] += valA * valB;
            }
        }
        for (int j = C.rowIndex.back(); j < C.colIndex.size(); ++j) {
            int col = C.colIndex[j];
            C.values.push_back(temp[col]);
            temp[col] = 0;
            marker[col] = false;
        }
        C.rowIndex.push_back(C.values.size());
    }
    return C;
}

std::vector<std::vector<int>> multiplyDenseCSR(const std::vector<std::vector<int>>& A, const CSRMatrix& B, int size) {
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = B.rowIndex[j]; k < B.rowIndex[j + 1]; ++k) {
                C[i][B.colIndex[k]] += A[i][j] * B.values[k];
            }
        }
    }
    return C;
}

void multiplyDenseDenseThread(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int startRow, int endRow) {
    int size = A.size();
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

std::vector<std::vector<int>> multiplyDenseDenseMT(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int numThreads) {
    int size = A.size();
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));
    std::vector<std::thread> threads;
    int rowsPerThread = size / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? size : startRow + rowsPerThread;
        threads.emplace_back(multiplyDenseDenseThread, std::cref(A), std::cref(B), std::ref(C), startRow, endRow);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return C;
}

void multiplyCSRDenseThread(const CSRMatrix& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int startRow, int endRow) {
    int size = B.size();
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = A.rowIndex[i]; k < A.rowIndex[i + 1]; ++k) {
                C[i][j] += A.values[k] * B[A.colIndex[k]][j];
            }
        }
    }
}

std::vector<std::vector<int>> multiplyCSRDenseMT(const CSRMatrix& A, const std::vector<std::vector<int>>& B, int numThreads) {
    int size = B.size();
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));
    std::vector<std::thread> threads;
    int rowsPerThread = size / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? size : startRow + rowsPerThread;
        threads.emplace_back(multiplyCSRDenseThread, std::cref(A), std::cref(B), std::ref(C), startRow, endRow);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return C;
}

void multiplyCSRCSRThread(const CSRMatrix& A, const CSRMatrix& B, CSRMatrix& localC, int startRow, int endRow, int size) {
    std::vector<int> temp(size, 0);
    std::vector<bool> marker(size, false);

    for (int i = startRow; i < endRow; ++i) {
        int rowStart = localC.colIndex.size();
        for (int j = A.rowIndex[i]; j < A.rowIndex[i + 1]; ++j) {
            int colA = A.colIndex[j];
            int valA = A.values[j];
            for (int k = B.rowIndex[colA]; k < B.rowIndex[colA + 1]; ++k) {
                int colB = B.colIndex[k];
                int valB = B.values[k];
                if (!marker[colB]) {
                    marker[colB] = true;
                    localC.colIndex.push_back(colB);
                }
                temp[colB] += valA * valB;
            }
        }
        for (int j = rowStart; j < localC.colIndex.size(); ++j) {
            int col = localC.colIndex[j];
            localC.values.push_back(temp[col]);
            temp[col] = 0;
            marker[col] = false;
        }
        localC.rowIndex.push_back(localC.values.size());
    }
}

CSRMatrix multiplyCSRCSRMT(const CSRMatrix& A, const CSRMatrix& B, int numThreads) {
    int size = A.rowIndex.size() - 1;
    CSRMatrix C;
    C.rowIndex.push_back(0);
    std::vector<std::thread> threads;
    std::vector<CSRMatrix> localCs(numThreads);
    int rowsPerThread = size / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        localCs[t].rowIndex.push_back(0);
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? size : startRow + rowsPerThread;
        threads.emplace_back(multiplyCSRCSRThread, std::cref(A), std::cref(B), std::ref(localCs[t]), startRow, endRow, size);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Merge local results into the final CSRMatrix C
    for (const auto& localC : localCs) {
        int offset = C.rowIndex.back();
        for (int i = 1; i < localC.rowIndex.size(); ++i) {
            C.rowIndex.push_back(localC.rowIndex[i] + offset);
        }
        C.colIndex.insert(C.colIndex.end(), localC.colIndex.begin(), localC.colIndex.end());
        C.values.insert(C.values.end(), localC.values.begin(), localC.values.end());
    }

    return C;
}

std::vector<std::vector<int>> multiplyDenseDenseMTSIMD(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int numThreads) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();
    
    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));

    // Ensure multithreading is handled
    std::vector<std::thread> threads(numThreads);
    for (int t = 0; t < numThreads; ++t) {
        threads[t] = std::thread([&, t]() {
            for (int i = t; i < rowsA; i += numThreads) {
                for (int j = 0; j < colsB; ++j) {
                    __m256i sum = _mm256_setzero_si256();

                    int k = 0;
                    // Process main blocks of 8 elements
                    for (; k <= colsA - 8; k += 8) {
                        // Load 8 elements from row A and 8 from the appropriate column of B
                        __m256i a = _mm256_loadu_si256((__m256i*)&A[i][k]);

                        // Manually gather elements of the column B
                        int b_vals[8] = { B[k][j], B[k + 1][j], B[k + 2][j], B[k + 3][j], B[k + 4][j], B[k + 5][j], B[k + 6][j], B[k + 7][j] };
                        __m256i b = _mm256_loadu_si256((__m256i*)b_vals);

                        // Multiply and accumulate
                        sum = _mm256_add_epi32(sum, _mm256_mullo_epi32(a, b));
                    }

                    // Handle the remaining elements when colsA is not a multiple of 8
                    int scalar_sum = 0;
                    for (; k < colsA; ++k) {
                        scalar_sum += A[i][k] * B[k][j];
                    }

                    // Sum all elements in the SIMD register
                    int temp[8];
                    _mm256_storeu_si256((__m256i*)temp, sum);

                    // Accumulate results from the SIMD part
                    for (int n = 0; n < 8; ++n) {
                        scalar_sum += temp[n];
                    }

                    C[i][j] = scalar_sum;
                }
            }
        });
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    return C;
}

std::vector<std::vector<int>> multiplyCSRDenseMTSIMD(const CSRMatrix& A, const std::vector<std::vector<int>>& B, int numThreads) {
    int rowsA = A.rowIndex.size() - 1;
    int colsB = B[0].size();
    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));

    #pragma omp parallel for num_threads(numThreads)
    for (int i = 0; i < rowsA; ++i) {
        for (int j = A.rowIndex[i]; j < A.rowIndex[i + 1]; ++j) {
            int colA = A.colIndex[j];
            int valA = A.values[j];

            int k = 0;
            for (; k <= colsB - 8; k += 8) {
                __m256i vecB = _mm256_loadu_si256((__m256i*)&B[colA][k]);
                __m256i vecC = _mm256_loadu_si256((__m256i*)&C[i][k]);
                __m256i vecA = _mm256_set1_epi32(valA);
                __m256i result = _mm256_add_epi32(vecC, _mm256_mullo_epi32(vecA, vecB));
                _mm256_storeu_si256((__m256i*)&C[i][k], result);
            }

            // Handle the remainder
            for (; k < colsB; ++k) {
                C[i][k] += valA * B[colA][k];
            }
        }
    }

    return C;
}

void multiplyCSRCSRThreadSIMD(const CSRMatrix& A, const CSRMatrix& B, CSRMatrix& localC, int startRow, int endRow, int size) {
    std::vector<int> temp(size, 0);
    std::vector<bool> marker(size, false);
    for (int i = startRow; i < endRow; ++i) {
        int rowStart = localC.colIndex.size();
        for (int j = A.rowIndex[i]; j < A.rowIndex[i + 1]; ++j) {
            int colA = A.colIndex[j];
            int valA = A.values[j];
            for (int k = B.rowIndex[colA]; k < B.rowIndex[colA + 1]; ++k) {
                int colB = B.colIndex[k];
                int valB = B.values[k];
                if (!marker[colB]) {
                    marker[colB] = true;
                    localC.colIndex.push_back(colB);
                }
                temp[colB] += valA * valB;
            }
        }
        for (int j = rowStart; j < localC.colIndex.size(); ++j) {
            int col = localC.colIndex[j];
            localC.values.push_back(temp[col]);
            temp[col] = 0;
            marker[col] = false;
        }
        localC.rowIndex.push_back(localC.values.size());
    }
}

CSRMatrix multiplyCSRCSRMTSIMD(const CSRMatrix& A, const CSRMatrix& B, int numThreads) {
    int size = A.rowIndex.size() - 1;
    CSRMatrix C;
    C.rowIndex.push_back(0);
    std::vector<std::thread> threads;
    std::vector<CSRMatrix> localCs(numThreads);
    int rowsPerThread = size / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        localCs[t].rowIndex.push_back(0);
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? size : startRow + rowsPerThread;
        threads.emplace_back(multiplyCSRCSRThreadSIMD, std::cref(A), std::cref(B), std::ref(localCs[t]), startRow, endRow, size);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Merge local results into the final CSRMatrix C
    for (const auto& localC : localCs) {
        int offset = C.rowIndex.back();
        for (int i = 1; i < localC.rowIndex.size(); ++i) {
            C.rowIndex.push_back(localC.rowIndex[i] + offset);
        }
        C.colIndex.insert(C.colIndex.end(), localC.colIndex.begin(), localC.colIndex.end());
        C.values.insert(C.values.end(), localC.values.begin(), localC.values.end());
    }

    return C;
}

void cacheMultiplyTileDenseDense(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int startRow, int endRow, int tileSize) {
    int size = A.size();
    for (int i = startRow; i < endRow; i += tileSize) {
        for (int j = 0; j < size; j += tileSize) {
            for (int k = 0; k < size; k += tileSize) {
                for (int ii = i; ii < std::min(i + tileSize, endRow); ++ii) {
                    for (int jj = j; jj < std::min(j + tileSize, size); ++jj) {
                        for (int kk = k; kk < std::min(k + tileSize, size); ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

std::vector<std::vector<int>> cacheMultiplyDenseDense(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int numThreads, int tileSize) {
    int size = A.size();
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));

    auto worker = [&](int start, int end) {
        cacheMultiplyTileDenseDense(A, B, C, start, end, tileSize);
    };

    std::vector<std::thread> threads;
    int chunkSize = size / numThreads;
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = (t == numThreads - 1) ? size : start + chunkSize;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return C;
}

void cacheMultiplyTileCSRCSR(const CSRMatrix& A, const CSRMatrix& B, CSRMatrix& localC, int startRow, int endRow, int tileSize, int size) {
    std::vector<int> temp(size, 0);
    std::vector<bool> marker(size, false);

    for (int i = startRow; i < endRow; i += tileSize) {
        for (int ii = i; ii < std::min(i + tileSize, endRow); ++ii) {
            for (int j = A.rowIndex[ii]; j < A.rowIndex[ii + 1]; ++j) {
                int colA = A.colIndex[j];
                int valA = A.values[j];
                for (int k = B.rowIndex[colA]; k < B.rowIndex[colA + 1]; ++k) {
                    int colB = B.colIndex[k];
                    int valB = B.values[k];
                    if (!marker[colB]) {
                        marker[colB] = true;
                        localC.colIndex.push_back(colB);
                    }
                    temp[colB] += valA * valB;
                }
            }
            for (int j = localC.rowIndex.back(); j < localC.colIndex.size(); ++j) {
                int col = localC.colIndex[j];
                localC.values.push_back(temp[col]);
                temp[col] = 0;
                marker[col] = false;
            }
            localC.rowIndex.push_back(localC.values.size());
        }
    }
}

CSRMatrix cacheMultiplyCSRCSR(const CSRMatrix& A, const CSRMatrix& B, int size, int numThreads, int tileSize) {
    CSRMatrix C;
    C.rowIndex.push_back(0);
    std::vector<std::thread> threads;
    std::vector<CSRMatrix> localCs(numThreads);
    int rowsPerThread = size / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        localCs[t].rowIndex.push_back(0);
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? size : startRow + rowsPerThread;
        threads.emplace_back(cacheMultiplyTileCSRCSR, std::cref(A), std::cref(B), std::ref(localCs[t]), startRow, endRow, tileSize, size);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Merge local results into the final CSRMatrix C
    for (const auto& localC : localCs) {
        int offset = C.rowIndex.back();
        for (int i = 1; i < localC.rowIndex.size(); ++i) {
            C.rowIndex.push_back(localC.rowIndex[i] + offset);
        }
        C.colIndex.insert(C.colIndex.end(), localC.colIndex.begin(), localC.colIndex.end());
        C.values.insert(C.values.end(), localC.values.begin(), localC.values.end());
    }

    return C;
}

void cacheMultiplyTileDenseCSR(const std::vector<std::vector<int>>& A, const CSRMatrix& B, std::vector<std::vector<int>>& C, int startRow, int endRow, int tileSize) {
    int size = A.size();
    for (int i = startRow; i < endRow; i += tileSize) {
        for (int j = 0; j < size; j += tileSize) {
            for (int ii = i; ii < std::min(i + tileSize, endRow); ++ii) {
                for (int jj = j; jj < std::min(j + tileSize, size); ++jj) {
                    for (int k = B.rowIndex[jj]; k < B.rowIndex[jj + 1]; ++k) {
                        C[ii][B.colIndex[k]] += A[ii][jj] * B.values[k];
                    }
                }
            }
        }
    }
}

std::vector<std::vector<int>> cacheMultiplyDenseCSR(const std::vector<std::vector<int>>& A, const CSRMatrix& B, int size, int numThreads, int tileSize) {
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));

    auto worker = [&](int start, int end) {
        cacheMultiplyTileDenseCSR(A, B, C, start, end, tileSize);
    };

    std::vector<std::thread> threads;
    int chunkSize = size / numThreads;
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = (t == numThreads - 1) ? size : start + chunkSize;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return C;
}

void cacheMultiplyTileDenseDenseSIMD(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int startRow, int endRow, int tileSize) {
    int size = A.size();
    for (int i = startRow; i < endRow; i += tileSize) {
        for (int j = 0; j < size; j += tileSize) {
            for (int k = 0; k < size; k += tileSize) {
                for (int ii = i; ii < std::min(i + tileSize, endRow); ++ii) {
                    for (int jj = j; jj < std::min(j + tileSize, size); ++jj) {
                        __m256i sum = _mm256_setzero_si256();
                        int kk = k;
                        for (; kk <= std::min(k + tileSize, size) - 8; kk += 8) {
                            __m256i a = _mm256_loadu_si256((__m256i*)&A[ii][kk]);
                            __m256i b = _mm256_loadu_si256((__m256i*)&B[kk][jj]);
                            sum = _mm256_add_epi32(sum, _mm256_mullo_epi32(a, b));
                        }
                        int scalar_sum = 0;
                        for (; kk < std::min(k + tileSize, size); ++kk) {
                            scalar_sum += A[ii][kk] * B[kk][jj];
                        }
                        int temp[8];
                        _mm256_storeu_si256((__m256i*)temp, sum);
                        for (int n = 0; n < 8; ++n) {
                            scalar_sum += temp[n];
                        }
                        C[ii][jj] += scalar_sum;
                    }
                }
            }
        }
    }
}

std::vector<std::vector<int>> cacheMultiplyDenseDenseSIMD(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int numThreads, int tileSize) {
    int size = A.size();
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));

    auto worker = [&](int start, int end) {
        cacheMultiplyTileDenseDenseSIMD(A, B, C, start, end, tileSize);
    };

    std::vector<std::thread> threads;
    int chunkSize = size / numThreads;
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = (t == numThreads - 1) ? size : start + chunkSize;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return C;
}

void cacheMultiplyTileDenseCSRSIMD(const std::vector<std::vector<int>>& A, const CSRMatrix& B, std::vector<std::vector<int>>& C, int startRow, int endRow, int tileSize) {
    int size = A[0].size();
    for (int i = startRow; i < endRow; i += tileSize) {
        for (int j = 0; j < size; j += tileSize) {
            for (int ii = i; ii < std::min(i + tileSize, endRow); ++ii) {
                for (int jj = j; jj < std::min(j + tileSize, size); ++jj) {
                    for (int k = B.rowIndex[jj]; k < B.rowIndex[jj + 1]; ++k) {
                        int colB = B.colIndex[k];
                        int valB = B.values[k];

                        int kk = 0;
                        for (; kk <= size - 8; kk += 8) {
                            __m256i vecA = _mm256_loadu_si256((__m256i*)&A[ii][kk]);
                            __m256i vecC = _mm256_loadu_si256((__m256i*)&C[colB][kk]);
                            __m256i vecB = _mm256_set1_epi32(valB);
                            __m256i result = _mm256_add_epi32(vecC, _mm256_mullo_epi32(vecA, vecB));
                            _mm256_storeu_si256((__m256i*)&C[colB][kk], result);
                        }

                        for (; kk < size; ++kk) {
                            C[colB][kk] += A[ii][kk] * valB;
                        }
                    }
                }
            }
        }
    }
}

std::vector<std::vector<int>> cacheMultiplyDenseCSRSIMD(const std::vector<std::vector<int>>& A, const CSRMatrix& B, int size, int numThreads, int tileSize) {
    int rowsA = size;
    int colsB = size;
    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));

    auto worker = [&](int start, int end) {
        cacheMultiplyTileDenseCSRSIMD(A, B, C, start, end, tileSize);
    };

    std::vector<std::thread> threads;
    int chunkSize = rowsA / numThreads;
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = (t == numThreads - 1) ? rowsA : start + chunkSize;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return C;
}

void cacheMultiplyTileCSRCSRSIMD(const CSRMatrix& A, const CSRMatrix& B, CSRMatrix& localC, int startRow, int endRow, int tileSize, int size) {
    std::vector<int> temp(size, 0);
    std::vector<bool> marker(size, false);

    for (int i = startRow; i < endRow; i += tileSize) {
        for (int ii = i; ii < std::min(i + tileSize, endRow); ++ii) {
            for (int j = A.rowIndex[ii]; j < A.rowIndex[ii + 1]; ++j) {
                int colA = A.colIndex[j];
                int valA = A.values[j];
                for (int k = B.rowIndex[colA]; k < B.rowIndex[colA + 1]; ++k) {
                    int colB = B.colIndex[k];
                    int valB = B.values[k];
                    if (!marker[colB]) {
                        marker[colB] = true;
                        localC.colIndex.push_back(colB);
                    }
                    temp[colB] += valA * valB;
                }
            }
            for (int j = localC.rowIndex.back(); j < localC.colIndex.size(); ++j) {
                int col = localC.colIndex[j];
                localC.values.push_back(temp[col]);
                temp[col] = 0;
                marker[col] = false;
            }
            localC.rowIndex.push_back(localC.values.size());
        }
    }
}

CSRMatrix cacheMultiplyCSRCSRSIMD(const CSRMatrix& A, const CSRMatrix& B, int size, int numThreads, int tileSize) {
    CSRMatrix C;
    C.rowIndex.push_back(0);
    std::vector<std::thread> threads;
    std::vector<CSRMatrix> localCs(numThreads);
    int rowsPerThread = size / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        localCs[t].rowIndex.push_back(0);
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? size : startRow + rowsPerThread;
        threads.emplace_back(cacheMultiplyTileCSRCSRSIMD, std::cref(A), std::cref(B), std::ref(localCs[t]), startRow, endRow, tileSize, size);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Merge local results into the final CSRMatrix C
    for (const auto& localC : localCs) {
        int offset = C.rowIndex.back();
        for (int i = 1; i < localC.rowIndex.size(); ++i) {
            C.rowIndex.push_back(localC.rowIndex[i] + offset);
        }
        C.colIndex.insert(C.colIndex.end(), localC.colIndex.begin(), localC.colIndex.end());
        C.values.insert(C.values.end(), localC.values.begin(), localC.values.end());
    }

    return C;
}

template <typename Func, typename... Args>
double timeFunction(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

// Main function to run tests and output results to CSV
int main() {
    std::vector<int> sizes = {2500};
    std::vector<double> sparsities = {0.001, 0.01, 0.1};
    std::vector<int> numThreads = {1, 8};
    std::vector<int> tileSizes = {256};

    std::ofstream csvFile("results1.csv");
    csvFile << "Size,Sparsity,Matrix A Type,Matrix B Type,Function,Threads,Tile Size,Time (ms)\n";
                    csvFile.flush();

    for (int size : sizes) {
        for (double sparsity : sparsities) {
            auto denseA = generateMatrix(size, 0.0);
            auto denseB = generateMatrix(size, 0.0);
            auto sparseA = convertToCSR(generateMatrix(size, sparsity));
            auto sparseB = convertToCSR(generateMatrix(size, sparsity));

            for (int threads : numThreads) {
                for (int tileSize : tileSizes) {
                    // Dense * Dense
                    csvFile << size << "," << sparsity << ",Dense,Dense,Unoptimized," << threads << "," << tileSize << "," << timeFunction(multiplyDenseDense, denseA, denseB) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Dense,Dense,Multithreaded," << threads << "," << tileSize << "," << timeFunction(multiplyDenseDenseMT, denseA, denseB, threads) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Dense,Dense,MT with SIMD," << threads << "," << tileSize << "," << timeFunction(multiplyDenseDenseMTSIMD, denseA, denseB, threads) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Dense,Dense,Cache Opt," << threads << "," << tileSize << "," << timeFunction(cacheMultiplyDenseDense, denseA, denseB, threads, tileSize) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Dense,Dense,Cache Opt SIMD," << threads << "," << tileSize << "," << timeFunction(cacheMultiplyDenseDenseSIMD, denseA, denseB, threads, tileSize) << "\n";
                    csvFile.flush();

                    // Sparse * Sparse
                    csvFile << size << "," << sparsity << ",Sparse,Sparse,Unoptimized," << threads << "," << tileSize << "," << timeFunction(multiplyCSRCSR, sparseA, sparseB, size) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Sparse,Sparse,Multithreaded," << threads << "," << tileSize << "," << timeFunction(multiplyCSRCSRMT, sparseA, sparseB, threads) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Sparse,Sparse,MT with SIMD," << threads << "," << tileSize << "," << timeFunction(multiplyCSRCSRMTSIMD, sparseA, sparseB, threads) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Sparse,Sparse,Cache Opt," << threads << "," << tileSize << "," << timeFunction(cacheMultiplyCSRCSR, sparseA, sparseB, size, threads, tileSize) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Sparse,Sparse,Cache Opt SIMD," << threads << "," << tileSize << "," << timeFunction(cacheMultiplyCSRCSRSIMD, sparseA, sparseB, size, threads, tileSize) << "\n";
                    csvFile.flush();

                    // Dense * Sparse
                    csvFile << size << "," << sparsity << ",Dense,Sparse,Unoptimized," << threads << "," << tileSize << "," << timeFunction(multiplyDenseCSR, denseA, sparseB, size) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Dense,Sparse,Multithreaded," << threads << "," << tileSize << "," << timeFunction(multiplyCSRDenseMT, sparseA, denseB, threads) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Dense,Sparse,MT with SIMD," << threads << "," << tileSize << "," << timeFunction(multiplyCSRDenseMTSIMD, sparseA, denseB, threads) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Dense,Sparse,Cache Opt," << threads << "," << tileSize << "," << timeFunction(cacheMultiplyDenseCSR, denseA, sparseB, size, threads, tileSize) << "\n";
                    csvFile.flush();
                    csvFile << size << "," << sparsity << ",Dense,Sparse,Cache Opt SIMD," << threads << "," << tileSize << "," << timeFunction(cacheMultiplyDenseCSRSIMD, denseA, sparseB, size, threads, tileSize) << "\n";
                    csvFile.flush();
                }
            }
        }
    }

    csvFile.close();
    std::cout << "Results written to results.csv" << std::endl;
    return 0;
}