#ifndef UTILITY_FUNCTIONS_CHOLESKY_DECOMPOSITION
#define UTILITY_FUNCTIONS_CHOLESKY_DECOMPOSITION

int generate_matrix_A(int dimension, 
    float matrix_A[dimension][dimension], 
    float matrix_G[dimension][dimension]);
int generate_matrix_G(int dimension, float matrix[dimension][dimension]);
int initialize_matrix_with_0(int dimension, float matrix[dimension][dimension]);
float frobenius_norm(int dimension,
                     float matrix_A[dimension][dimension],
                     float matrix_L[dimension][dimension]);
void print_matrix(int dimension, float matrix[dimension][dimension]);


#endif