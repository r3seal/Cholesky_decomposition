#include "cholesky_decomposition.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #define DEBUG_TEST

int test_dimension_and_process(int dimension, int p, char delimeter) {

    #ifdef DEBUG_TEST
        struct timespec malloc_start_time, malloc_end_time;
        clock_gettime(CLOCK_MONOTONIC, &malloc_start_time);
    #endif 

    double (*matrix_G)[dimension] = malloc(dimension * sizeof(*matrix_G));
    if (matrix_G == NULL) {
        fprintf(stderr, "Brak pamieci dla macierzy A (n=%d)\n", dimension);
        return 1;
    }
    double (*matrix_Lt)[dimension] = malloc(dimension * sizeof(*matrix_Lt));
    if (matrix_Lt == NULL) {
        fprintf(stderr, "Brak pamieci dla macierzy A (n=%d)\n", dimension);
        return 1;
    }
    double (*matrix_A)[dimension] = malloc(dimension * sizeof(*matrix_A));
    if (matrix_A == NULL) {
        fprintf(stderr, "Brak pamieci dla macierzy A (n=%d)\n", dimension);
        return 1;
    }

    #ifdef DEBUG_TEST
        clock_gettime(CLOCK_MONOTONIC, &malloc_end_time);
        double malloc_delta_time = (malloc_end_time.tv_sec - malloc_start_time.tv_sec) + 1e-9 * (malloc_end_time.tv_nsec - malloc_start_time.tv_nsec);
        printf("Malloc time %.6e\n", malloc_delta_time);
    #endif 

    #ifdef DEBUG_TEST
        struct timespec initialization_start_time, initialization_end_time;
        clock_gettime(CLOCK_MONOTONIC, &initialization_start_time);
    #endif  
    
    initialize_matrix_with_0(dimension, matrix_G);
    initialize_matrix_with_0(dimension, matrix_Lt);
    initialize_matrix_with_0(dimension, matrix_A);

    #ifdef DEBUG_TEST
        clock_gettime(CLOCK_MONOTONIC, &initialization_end_time);
        double initialization_delta_time = (initialization_end_time.tv_sec - initialization_start_time.tv_sec) + 1e-9 * (initialization_end_time.tv_nsec - initialization_start_time.tv_nsec);
        printf("Initialization time %.6e\n", initialization_delta_time);
    #endif

    #ifdef DEBUG_TEST
        struct timespec matrix_G_generation_start_time, matrix_G_generation_end_time;
        clock_gettime(CLOCK_MONOTONIC, &matrix_G_generation_start_time);
    #endif

    generate_matrix_G(dimension, matrix_G);

    #ifdef DEBUG_TEST
        clock_gettime(CLOCK_MONOTONIC, &matrix_G_generation_end_time);
        double matrix_G_generation_delta_time = (matrix_G_generation_end_time.tv_sec - matrix_G_generation_start_time.tv_sec) + 1e-9 * (matrix_G_generation_end_time.tv_nsec - matrix_G_generation_start_time.tv_nsec);
        printf("Matrix G generation time %.6e\n", matrix_G_generation_delta_time);
    #endif

    #ifdef DEBUG_TEST
        struct timespec matrix_A_generation_start_time, matrix_A_generation_end_time;
        clock_gettime(CLOCK_MONOTONIC, &matrix_A_generation_start_time);
    #endif

    generate_matrix_A(dimension, matrix_A, matrix_G);

    #ifdef DEBUG_TEST
        clock_gettime(CLOCK_MONOTONIC, &matrix_A_generation_end_time);
        double matrix_A_generation_delta_time = (matrix_A_generation_end_time.tv_sec - matrix_A_generation_start_time.tv_sec) + 1e-9 * (matrix_A_generation_end_time.tv_nsec - matrix_A_generation_start_time.tv_nsec);
        printf("Matrix A generation time %.6e\n", matrix_A_generation_delta_time);
    #endif 

    #ifdef DEBUG_TEST
        struct timespec original_matrix_A_start_time, original_matrix_A_end_time;
        clock_gettime(CLOCK_MONOTONIC, &original_matrix_A_start_time);
    #endif

    double (*original_matrix_A)[dimension] = malloc(dimension * sizeof(*original_matrix_A)); 
    memcpy(original_matrix_A, matrix_A, dimension * sizeof(*matrix_A));

    #ifdef DEBUG_TEST
        clock_gettime(CLOCK_MONOTONIC, &original_matrix_A_end_time);
        double original_matrix_A_delta_time = (original_matrix_A_end_time.tv_sec - original_matrix_A_start_time.tv_sec) + 1e-9 * (original_matrix_A_end_time.tv_nsec - original_matrix_A_start_time.tv_nsec);
        printf("Original matrix A time %.6e\n", original_matrix_A_delta_time);
    #endif 

    check_correctness(dimension, matrix_A);

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    cholesky_decomposition(dimension, matrix_A, matrix_Lt);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double delta_time = (end_time.tv_sec - start_time.tv_sec) + 1e-9 * (end_time.tv_nsec - start_time.tv_nsec);

    #ifdef DEBUG_TEST
        struct timespec norm_A_start_time, norm_A_end_time;
        clock_gettime(CLOCK_MONOTONIC, &norm_A_start_time);
    #endif

    double norm_A = frobenius_norm_of(dimension, original_matrix_A);

    #ifdef DEBUG_TEST
        clock_gettime(CLOCK_MONOTONIC, &norm_A_end_time);
        double norm_A_delta_time = (norm_A_end_time.tv_sec - norm_A_start_time.tv_sec) + 1e-9 * (norm_A_end_time.tv_nsec - norm_A_start_time.tv_nsec);
        printf("Norm A time %.6e\n", norm_A_delta_time);
    #endif

    #ifdef DEBUG_TEST
        struct timespec norm_start_time, norm_end_time;
        clock_gettime(CLOCK_MONOTONIC, &norm_start_time);
    #endif

    double error = frobenius_norm(dimension, original_matrix_A, matrix_Lt);

    #ifdef DEBUG_TEST
        clock_gettime(CLOCK_MONOTONIC, &norm_end_time);
        double norm_delta_time = (norm_end_time.tv_sec - norm_start_time.tv_sec) + 1e-9 * (norm_end_time.tv_nsec - norm_start_time.tv_nsec);
        printf("Norm time %.6e\n", norm_delta_time);
    #endif

    print_row("seq", dimension, p, delta_time, error, error / norm_A, delimeter);

    free(matrix_G);
    free(matrix_Lt);
    free(matrix_A);
    free(original_matrix_A);

    return 0;
}

int run_tests(int max_dimension, char delimiter) {
    print_header(delimiter);
    for (int dimension = 4; dimension <= max_dimension + 5; dimension += 100) {
        test_dimension_and_process(dimension, 1, delimiter);
    }
    
    return 0;
}