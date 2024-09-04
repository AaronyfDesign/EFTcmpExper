#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 矩阵大小
#define SIZE 295

// EFT两数之和
void TwoSum(double a, double b, double* sum, double* error) {
    *sum = a + b;
    double b_virtual = *sum - a;
    double a_virtual = *sum - b_virtual;
    *error = (a - a_virtual) + (b - b_virtual);
}

// EFT求和
void EFTAdd(double a, double b, double* result, double* error) {
    double sum, e;
    TwoSum(a, b, &sum, &e);
    *result = sum;
    *error = e;
}

// EFT两数之积
void TwoProd(double a, double b, double* prod, double* error) {
    *prod = a * b;
    double a_high, a_low, b_high, b_low;

    const double split = 134217729.0; // 2^27 + 1, 用于浮点数分解

    a_high = a * split;
    a_low = a - a_high;
    a_high = a_high + a_low - a;
    a_low = a - a_high;

    b_high = b * split;
    b_low = b - b_high;
    b_high = b_high + b_low - b;
    b_low = b - b_high;

    *error = ((a_high * b_high - *prod) + a_high * b_low + a_low * b_high) + a_low * b_low;
}

// EFT乘法运算
void EFTMul(double a, double b, double* result, double* error) {
    double prod, e;
    TwoProd(a, b, &prod, &e);
    *result = prod;
    *error = e;
}

// 初始化矩阵
void initialize_matrix(double matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = (double)(rand() % 100) / 10.0;
        }
    }
}

// EFT矩阵乘法
void EFTMatrixMultiplication(double A[SIZE][SIZE], double B[SIZE][SIZE], double C[SIZE][SIZE], double* total_error) {
    *total_error = 0.0;  // 初始化总误差为0

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            double sum = 0.0;
            double sum_error = 0.0;

            for (int k = 0; k < SIZE; k++) {
                double product, product_error;
                double A_ik = A[i][k];
                double B_kj = B[k][j];

                EFTMul(A_ik, B_kj, &product, &product_error);

                double old_sum = sum;
                double old_sum_error = sum_error;

                EFTAdd(sum, product, &sum, &sum_error);

                // double error_adjustment;
                // EFTAdd(old_sum_error, product_error, &error_adjustment, &sum_error);
                // *total_error += error_adjustment;
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    double total_error;
    srand(time(NULL));
    initialize_matrix(A);
    initialize_matrix(B);

    clock_t start_time, end_time;

    start_time = clock();
    EFTMatrixMultiplication(A, B, C, &total_error);
    end_time = clock();

    printf("EFT Matrix Multiplication Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    // printf("Total Floating-Point Error: %e\n", total_error);

    return 0;
}
