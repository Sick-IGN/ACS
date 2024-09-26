#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024 * 1024 * 1024 // Length of 1D array

// Function to multiply two 1D arrays with a specific step
void multiply_arrays(int *a, int *b, int *result, int step) {
    for (int i = 0; i < step; i++) {
        for (int j = 0; j < SIZE; j += step) {
            result[i] += a[i] * b[j]; // Multiply a[i] with every b[j]
        }
    }
}

int main() {
    srand(time(NULL));

    int *array1 = malloc(SIZE * sizeof(int));
    int *array2 = malloc(SIZE * sizeof(int));
    int *result = calloc(SIZE, sizeof(int)); // Initialize result to zero

    // Initialize arrays with random numbers
    for (int i = 0; i < SIZE; i++) {
        array1[i] = rand() % 10;
        array2[i] = rand() % 10;
    }

    // Multiply with a step of 1
    clock_t start_time = clock();
    multiply_arrays(array1, array2, result, 1);
    clock_t end_time = clock();
    double time_taken_step_1 = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Time taken with step 1: %.6f seconds\n", time_taken_step_1);

    // Reset result array
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0; // Reset result for the next computation
    }

    // Multiply with a step of 512
    start_time = clock();
    multiply_arrays(array1, array2, result, 512);
    end_time = clock();
    double time_taken_step_512 = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Time taken with step 512: %.6f seconds\n", time_taken_step_512);

    // Reset result array
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0; // Reset result for the next computation
    }

    // Multiply with a step of 1024 
    start_time = clock();
    multiply_arrays(array1, array2, result, 1024);
    end_time = clock();
    double time_taken_step_1024 = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Time taken with step 1024: %.6f seconds\n", time_taken_step_1024);

    // Reset result array
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0; // Reset result for the next computation
    }

    // Multiply with a step of 1024 * 10
    start_time = clock();
    multiply_arrays(array1, array2, result, 1024 * 10);
    end_time = clock();
    double time_taken_step_1024_10 = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Time taken with step 1024 * 10: %.6f seconds\n", time_taken_step_1024_10);
    
    
    // Free allocated memory
    free(array1);
    free(array2);
    free(result);

    return 0;
}
