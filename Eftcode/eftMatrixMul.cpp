#include <stdio.h>
#include <stdlib.h>
#include "../lib/libeft.h"
#include <time.h>

// 矩阵大小
#define SIZE 295

// 初始化矩阵
void initialize_matrix(double matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = (double)(rand() % 100) / 10.0;
        }
    }
}

// EFT矩阵乘法
void EFTMatrixMultiplication(double A[SIZE][SIZE], double B[SIZE][SIZE], double C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            double sum = 0.0;
            for (int k = 0; k < SIZE; k++) {
                double product;
                EFTMul(A[i][k], B[k][j], &product);
                //product = A[i][k] * B[k][j];
                EFTAdd(sum, product, &sum);
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    srand(time(NULL));
    initialize_matrix(A);
    initialize_matrix(B);

    clock_t start_time, end_time;

    start_time = clock();
    EFTMatrixMultiplication(A, B, C);
    end_time = clock();

    printf("EFT Matrix Multiplication Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
