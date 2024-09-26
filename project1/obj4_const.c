#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2000

// Function to multiply two const arrays
void multiply_const_arrays(const int *const *a, const int *const *b, int **result) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0; // Initialize result to zero
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Function to initialize arrays with random 1-digit numbers
void initialize_array(int **array) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            array[i][j] = rand() % 10; // Random 1-digit number (0-9)
        }
    }
}

// Helper function to allocate a 2D array
int** allocate_2d_array() {
    int **array = malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        array[i] = malloc(SIZE * sizeof(int));
    }
    return array;
}

// Helper function to free a 2D array
void free_2d_array(int **array) {
    for (int i = 0; i < SIZE; i++) {
        free(array[i]);
    }
    free(array);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Allocate const arrays and result array
    int **array3 = allocate_2d_array();
    int **array4 = allocate_2d_array();
    int **result2 = allocate_2d_array();

    // Initialize const arrays
    initialize_array(array3);
    initialize_array(array4);

    // Start timing for const multiplication
    clock_t start_time = clock();
    multiply_const_arrays((const int **)array3, (const int *const *)array4, result2);
    clock_t end_time = clock();
    double time_taken_const = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Print time taken for the const multiplication
    printf("Time taken for multiplication with const arrays: %.6f seconds\n", time_taken_const);

    // Free allocated memory
    free_2d_array(array3);
    free_2d_array(array4);
    free_2d_array(result2);

    return 0;
}
