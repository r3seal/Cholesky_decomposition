#ifndef UTILITY_FUNCTIONS_CHOLESKY_DECOMPOSITION
#define UTILITY_FUNCTIONS_CHOLESKY_DECOMPOSITION

int generate_matrix_A(int dimension, 
    double matrix_A[dimension][dimension], 
    double matrix_G[dimension][dimension]);
int generate_matrix_G(int dimension, double matrix[dimension][dimension]);
int initialize_matrix_with_0(int dimension, double matrix[dimension][dimension]);

double frobenius_norm(int dimension,
                     double matrix_A[dimension][dimension],
                     double matrix_L[dimension][dimension]);
double frobenius_norm_of(int dimension, double matrix_A[dimension][dimension]);

int check_correctness(int dimension, double matrix[dimension][dimension]);

void print_matrix(int dimension, double matrix[dimension][dimension]);
void print_header(char delimiter);
void print_row(const char *name, int n, int p, double t, double err, double norm_err, char delimiter);


#endif