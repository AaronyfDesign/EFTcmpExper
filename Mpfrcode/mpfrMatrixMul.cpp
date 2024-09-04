#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>
#include <time.h>

// 矩阵大小
#define SIZE 295

// 初始化矩阵
void initialize_matrix_mpfr(mpfr_t matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mpfr_set_d(matrix[i][j], (double)(rand() % 100) / 10.0, MPFR_RNDN);
        }
    }
}

// MPFR矩阵乘法
void MPFRMatrixMultiplication(mpfr_t A[SIZE][SIZE], mpfr_t B[SIZE][SIZE], mpfr_t C[SIZE][SIZE]) {
    mpfr_t sum, product;
    mpfr_inits2(256, sum, product, NULL);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mpfr_set_d(sum, 0.0, MPFR_RNDN);
            for (int k = 0; k < SIZE; k++) {
                mpfr_mul(product, A[i][k], B[k][j], MPFR_RNDN);
                mpfr_add(sum, sum, product, MPFR_RNDN);
            }
            mpfr_set(C[i][j], sum, MPFR_RNDN);
        }
    }

    mpfr_clears(sum, product, NULL);
}

int main() {
    mpfr_t A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mpfr_inits2(256, A[i][j], B[i][j], C[i][j], NULL);
        }
    }

    initialize_matrix_mpfr(A);
    initialize_matrix_mpfr(B);

    clock_t start_time, end_time;

    start_time = clock();
    MPFRMatrixMultiplication(A, B, C);
    end_time = clock();

    printf("MPFR Matrix Multiplication Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // 清除MPFR变量
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mpfr_clears(A[i][j], B[i][j], C[i][j], NULL);
        }
    }

    return 0;
}
