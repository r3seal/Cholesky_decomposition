#include "cholesky_decomposition.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cholesky_decomposition(int dimension, 
    float matrix_A[dimension][dimension], 
    float matrix_L[dimension][dimension]) {

    for (int col = 0; col < dimension-1; col++) {
        matrix_L[col][col] = sqrt(matrix_A[col][col]);
        
        for (int row = col + 1; row < dimension; row++) {
            matrix_L[row][col] = matrix_A[row][col] / matrix_L[col][col];
        }

        for (int r_col = col + 1; r_col < dimension; r_col++) {
            for (int row = r_col; row < dimension; row++) {
                matrix_A[row][r_col] -= matrix_L[row][col]*matrix_L[r_col][col];
            }
        }

    }
    matrix_L[dimension-1][dimension-1] = sqrt(matrix_A[dimension-1][dimension-1]);

    return 0;
}