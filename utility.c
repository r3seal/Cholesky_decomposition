#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int generate_matrix_A(
    int dimension,
    double matrix_A[dimension][dimension],
    double matrix_G[dimension][dimension]) {
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            for (int i = 0; i < dimension; i++) {
                matrix_A[row][col] += matrix_G[row][i] * matrix_G[col][i];
            }
        }
    }

    return 0;
}

int generate_matrix_G(int dimension, double matrix[dimension][dimension]) {
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            matrix[row][col] = 2.0 * rand() / RAND_MAX - 1.0;
        }
    }

    return 0;
}

int initialize_matrix_with_0(int dimension, double matrix[dimension][dimension]) {
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            matrix[row][col] = 0;
        }
    }

    return 0;
}

double frobenius_norm(int dimension,
                     double matrix_A[dimension][dimension],
                     double matrix_Lt[dimension][dimension]) {
    double sum = 0.0;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            double product = 0.0;

            for (int k = 0; k < dimension; k++) {
                product += matrix_Lt[k][i] * matrix_Lt[k][j];
            }

            double difference = product - matrix_A[i][j];
            sum += difference * difference;
        }
    }

    return sqrt(sum);
}

void print_matrix(int dimension, double matrix[dimension][dimension]) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%10.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int check_correctness(int dimension, double matrix[dimension][dimension]) {
    for (int col = 0; col < dimension; col++) {
        if (matrix[col][col] <= 0.0) return -1;
    }

    return 0;
}

double frobenius_norm_of(int dimension, double matrix_A[dimension][dimension]) {
    double s = 0.0;
    for (int row = 0; row < dimension; row++)
        for (int col = 0; col < dimension; col++)
            s += matrix_A[row][col] * matrix_A[row][col];
    return sqrt(s);
}

void print_header(char delimiter) {
    printf("name%cdimension%cp%cdelta_time%cerror%cnorm_error\n",
           delimiter, delimiter, delimiter, delimiter, delimiter);
}

void print_row(const char *name, int n, int p, double t, double err, double norm_err, char delimiter) {
    printf("%s%c%d%c%d%c%.6f%c%.6e%c%.6e\n",
           name, delimiter, n, delimiter, p, delimiter,
           t, delimiter, err, delimiter, norm_err);
}