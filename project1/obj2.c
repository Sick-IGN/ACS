#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_SIZE (1024 * 1024 * 1024) // 1 GB

void measure_bandwidth(size_t granularity, double read_ratio) {
    size_t size = MAX_SIZE / granularity * granularity; // Ensure the size is a multiple of granularity
    char *buffer = malloc(size);
    if (!buffer) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Initialize the buffer
    memset(buffer, 1, size);

    struct timespec start, end;
    double elapsed_time;

    // Measure read performance
    if (read_ratio > 0) { // Read phase (if applicable)
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (size_t i = 0; i < size; i += granularity) {
            volatile char temp = buffer[i]; // Use volatile to prevent optimization
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("| Read  | Granularity: %5zuB | Ratio: %5.2f | Bandwidth: %8.2f GB/s |\n",
               granularity, read_ratio, (size / (1024.0 * 1024.0 * 1024.0)) / elapsed_time);
    }

    // Measure write performance
    if (read_ratio < 1) { // Write phase (if applicable)
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (size_t i = 0; i < size; i += granularity) {
            memcpy(&buffer[i], &i, granularity); // Write to buffer
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("| Write | Granularity: %5zuB | Ratio: %5.2f | Bandwidth: %8.2f GB/s |\n",
               granularity, read_ratio, (size / (1024.0 * 1024.0 * 1024.0)) / elapsed_time);
    }

    free(buffer);
}

int main() {
    size_t granularities[] = {64, 256, 1024, 64 * 1024, 256 * 1024, 1024 * 1024};
    double ratios[] = {1.0, 0.7, 0.5, 0.3, 0.0}; // Ordered: Read-only, 70:30, 50:50, 30:70, Write-only

    printf("=========================================================================\n");
    printf("| Type  |     Granularity     |  Read Ratio  |        Bandwidth         |\n");
    printf("=========================================================================\n");

    for (size_t i = 0; i < sizeof(granularities) / sizeof(granularities[0]); ++i) {
        for (size_t j = 0; j < sizeof(ratios) / sizeof(ratios[0]); ++j) {
            double read_ratio = ratios[j];
            double write_ratio = 1.0 - read_ratio;

            // Measure read and write bandwidths
            measure_bandwidth(granularities[i], read_ratio);
            printf("=========================================================================\n");
        }
        printf("=========================================================================\n");
    }

    printf("=========================================================================\n");
    return 0;
}
