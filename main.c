#include "cholesky_decomposition.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG

int main() {
    int dimension = 6;

    float (*matrix_G)[dimension] = malloc(dimension * sizeof(*matrix_G));
    float (*matrix_L)[dimension] = malloc(dimension * sizeof(*matrix_L));
    float (*matrix_A)[dimension] = malloc(dimension * sizeof(*matrix_A));
    
    initialize_matrix_with_0(dimension, matrix_G);
    initialize_matrix_with_0(dimension, matrix_L);
    initialize_matrix_with_0(dimension, matrix_A);

    generate_matrix_G(dimension, matrix_G);
    generate_matrix_A(dimension, matrix_A, matrix_G);

    #ifdef DEBUG
        printf("Matrix G\n");
        print_matrix(dimension, matrix_G);
        printf("Matrix A\n");
        print_matrix(dimension, matrix_A);
    #endif

    float (*original_matrix_A)[dimension] = malloc(dimension * sizeof(*original_matrix_A)); 
    memcpy(original_matrix_A, matrix_A, dimension * sizeof(*matrix_A));

    cholesky_decomposition(dimension, matrix_A, matrix_L);

    #ifdef DEBUG
        printf("Matrix L\n");
        print_matrix(dimension, matrix_L);
    #endif

    float error = frobenius_norm(dimension, original_matrix_A, matrix_L);
    printf("Frobenius norm: %f\n", error);



    free(matrix_G);
    free(matrix_L);
    free(matrix_A);
    free(original_matrix_A);

    return 0;
}