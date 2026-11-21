#include "cholesky_decomposition.h"
#include "utility.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG

int main() {
    srand(42);

    #ifdef DEBUG

    int dimension = 6;

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
    
    initialize_matrix_with_0(dimension, matrix_G);
    initialize_matrix_with_0(dimension, matrix_Lt);
    initialize_matrix_with_0(dimension, matrix_A);

    generate_matrix_G(dimension, matrix_G);
    generate_matrix_A(dimension, matrix_A, matrix_G);

    
    printf("Matrix G\n");
    print_matrix(dimension, matrix_G);
    printf("Matrix A\n");
    print_matrix(dimension, matrix_A);

    double (*original_matrix_A)[dimension] = malloc(dimension * sizeof(*original_matrix_A)); 
    memcpy(original_matrix_A, matrix_A, dimension * sizeof(*matrix_A));

    check_correctness(dimension, matrix_A);

    cholesky_decomposition(dimension, matrix_A, matrix_Lt);

    printf("Matrix L_t\n");
    print_matrix(dimension, matrix_Lt);

    double error = frobenius_norm(dimension, original_matrix_A, matrix_Lt);
    printf("Frobenius norm: %f\n", error);



    free(matrix_G);
    free(matrix_Lt);
    free(matrix_A);
    free(original_matrix_A);

    test_dimension_and_process(3000, 1, ';');



    #endif


    #ifndef DEBUG
    int two_minutes_dimension = 8500; 
    //8500 - 100 seconds
    // name;dimension;p;delta_time;error;norm_error
    // seq;8500;1;102.854105;9.014098e-10;2.440455e-15

    char delimeter = ';';

    run_tests(two_minutes_dimension, delimeter);

    #endif

    return 0;
}