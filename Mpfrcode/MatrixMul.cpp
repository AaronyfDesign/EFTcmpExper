#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>
#include <time.h>
#include <math.h>

// 矩阵大小
#define SIZE 295

// 初始化MPFR矩阵
void initialize_matrix_mpfr(mpfr_t matrix[SIZE][SIZE], const double init_matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mpfr_set_d(matrix[i][j], init_matrix[i][j], MPFR_RNDN);
        }
    }
}

// 初始化常规浮点数矩阵
void initialize_matrix_double(double matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = (double)(rand() % 100) / 10.0;
        }
    }
}

// MPFR矩阵乘法
void MPFRMatrixMultiplication(mpfr_t A[SIZE][SIZE], mpfr_t B[SIZE][SIZE], mpfr_t C[SIZE][SIZE], double a[SIZE][SIZE], double b[SIZE][SIZE], double c[SIZE][SIZE]) {
    mpfr_t sum, product;
    mpfr_inits2(256, sum, product, NULL);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mpfr_set_d(sum, 0.0, MPFR_RNDN);
            c[i][j] = 0.0;
            for (int k = 0; k < SIZE; k++) {
                mpfr_mul(product, A[i][k], B[k][j], MPFR_RNDN);
                mpfr_add(sum, sum, product, MPFR_RNDN);
                c[i][j] += a[i][k] * b[k][j];
            }
            mpfr_t mpfr_val, error;
            mpfr_inits2(256, mpfr_val, error, NULL);
            mpfr_set_d(mpfr_val, c[i][j], MPFR_RNDN);
            mpfr_sub(error, C[i][j], mpfr_val, MPFR_RNDN);
            mpfr_set(C[i][j], sum, MPFR_RNDN);
        }
    }

    mpfr_clears(sum, product, NULL);
}

// 常规浮点数矩阵乘法
void DoubleMatrixMultiplication(double A[SIZE][SIZE], double B[SIZE][SIZE], double C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// 计算矩阵误差
double compute_matrix_error(mpfr_t MPFRMatrix[SIZE][SIZE], double doubleMatrix[SIZE][SIZE]) {
    double max_error = 0.0;
    mpfr_t diff;
    mpfr_init2(diff, 256);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mpfr_t mpfr_val, error;
            mpfr_inits2(256, mpfr_val, error, NULL);
            mpfr_set_d(mpfr_val, doubleMatrix[i][j], MPFR_RNDN);
            mpfr_sub(error,MPFRMatrix[i][j] , mpfr_val, MPFR_RNDN);
            //double error = fabs(mpfr_val - doubleMatrix[i][j]);
            //if (error > max_error) {
            //    max_error = error;
            //}
        }
    }

    mpfr_clear(diff);
    return max_error;
}

int main() {
    mpfr_t A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    double A_double[SIZE][SIZE], B_double[SIZE][SIZE], C_double[SIZE][SIZE];
    srand(time(NULL));

    // 初始化常规浮点数矩阵
    initialize_matrix_double(A_double);
    initialize_matrix_double(B_double);

    // 使用常规浮点数矩阵初始化MPFR矩阵
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mpfr_inits2(256, A[i][j], B[i][j], C[i][j], NULL);
        }
    }
    initialize_matrix_mpfr(A, A_double);
    initialize_matrix_mpfr(B, B_double);

    // 进行MPFR矩阵乘法
    clock_t start_time, end_time;

    start_time = clock();
    MPFRMatrixMultiplication(A, B, C, A_double, B_double, C_double);
    end_time = clock();
    printf("MPFR Matrix Multiplication Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // 进行常规浮点数矩阵乘法
    // start_time = clock();
    // DoubleMatrixMultiplication(A_double, B_double, C_double);
    // end_time = clock();
    // printf("Double Matrix Multiplication Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // 计算和打印误差
    // double max_error = compute_matrix_error(C, C_double);
    // printf("Maximum Error between MPFR and Double Precision matrices: %e\n", max_error);

    // 清除MPFR变量
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mpfr_clears(A[i][j], B[i][j], C[i][j], NULL);
        }
    }

    return 0;
}
