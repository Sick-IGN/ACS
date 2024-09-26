#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2000

// Function to multiply two volatile arrays
void multiply_volatile_arrays(volatile int **a, volatile int **b, int **result) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0; // Initialize result to zero
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Function to initialize volatile arrays with random 1-digit numbers
void initialize_volatile_array(volatile int **array) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            array[i][j] = rand() % 10; // Random 1-digit number (0-9)
        }
    }
}

// Helper function to allocate a volatile 2D array
volatile int** allocate_volatile_2d_array() {
    volatile int **array = malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        array[i] = malloc(SIZE * sizeof(int));
    }
    return array;
}

// Helper function to allocate a regular 2D array
int** allocate_2d_array() {
    int **array = malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        array[i] = malloc(SIZE * sizeof(int));
    }
    return array;
}

// Helper function to free a volatile 2D array
void free_volatile_2d_array(volatile int **array) {
    for (int i = 0; i < SIZE; i++) {
        free((void *)array[i]); // Cast to void* to avoid warnings
    }
    free((void *)array); // Cast to void* to avoid warnings
}

// Helper function to free a regular 2D array
void free_2d_array(int **array) {
    for (int i = 0; i < SIZE; i++) {
        free(array[i]);
    }
    free(array);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Allocate volatile arrays and result array
    volatile int **array1 = allocate_volatile_2d_array();
    volatile int **array2 = allocate_volatile_2d_array();
    int **result1 = allocate_2d_array();

    // Initialize volatile arrays
    initialize_volatile_array(array1);
    initialize_volatile_array(array2);

    // Start timing for volatile multiplication
    clock_t start_time = clock();
    multiply_volatile_arrays(array1, array2, result1);
    clock_t end_time = clock();
    double time_taken_volatile = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Print time taken for the volatile multiplication
    printf("Time taken for multiplication with volatile arrays: %.6f seconds\n", time_taken_volatile);

    // Free allocated memory
    free_volatile_2d_array(array1);
    free_volatile_2d_array(array2);
    free_2d_array(result1);

    return 0;
}
