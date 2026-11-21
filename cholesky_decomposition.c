#include "cholesky_decomposition.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cholesky_decomposition(int dimension, 
    double matrix_A[dimension][dimension], 
    double matrix_Lt[dimension][dimension]) {

    for (int col = 0; col < dimension-1; col++) {
        double l_col_col = sqrt(matrix_A[col][col]);
        matrix_Lt[col][col] = l_col_col;
        
        for (int row = col + 1; row < dimension; row++) {
            matrix_Lt[col][row] = matrix_A[col][row] / l_col_col;
        }

        for (int r_col = col + 1; r_col < dimension; r_col++) {
            double L_col_rcol = matrix_Lt[col][r_col];
            for (int row = r_col; row < dimension; row++) {
                matrix_A[r_col][row] -= matrix_Lt[col][row]*L_col_rcol;
            }
        }

    }
    matrix_Lt[dimension-1][dimension-1] = sqrt(matrix_A[dimension-1][dimension-1]);

    return 0;
}