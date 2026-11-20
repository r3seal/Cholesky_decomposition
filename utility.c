#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int generate_matrix_A(
    int dimension,
    float matrix_A[dimension][dimension],
    float matrix_G[dimension][dimension]) {
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            for (int i = 0; i < dimension; i++) {
                matrix_A[row][col] += matrix_G[row][i] * matrix_G[col][i];
            }
        }
    }

    return 0;
}

int generate_matrix_G(int dimension, float matrix[dimension][dimension]) {
    // change the random to be global
    int max_value = 1000;
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            if (row >= col) {
                matrix[row][col] = rand() % (max_value + 1);
            }
        }
    }

    return 0;
}

    // initialize L matrix
int initialize_matrix_with_0(int dimension, float matrix[dimension][dimension]) {
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            matrix[row][col] = 0;
        }
    }

    return 0;
}

float frobenius_norm(int dimension,
                     float matrix_A[dimension][dimension],
                     float matrix_L[dimension][dimension]) {
    double sum = 0.0;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            double product = 0.0;

            for (int k = 0; k < dimension; k++) {
                product += (double)matrix_L[i][k] * matrix_L[j][k];
            }

            double difference = product - matrix_A[i][j];
            sum += difference * difference;
        }
    }

    return (float)sqrt(sum);
}

void print_matrix(int dimension, float matrix[dimension][dimension]) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%10.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
    