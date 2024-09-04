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
void MatrixMultiplication(double A[SIZE][SIZE], double B[SIZE][SIZE], double C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            double sum = 0.0;
            for (int k = 0; k < SIZE; k++) {
                double product, op1, op2;
                //op1 = A[i][k], op2 = B[k][j];
                //EFTMul(A[i][k], B[k][j], &product);
                product = A[i][k] * B[k][j];
                //EFTAdd(sum, product, &sum);
                sum += product; 
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
    MatrixMultiplication(A, B, C);
    end_time = clock();

    printf("BASE Matrix Multiplication Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}


/*

// EFT两数之和
void TwoSum(double a, double b, double* sum, double* error) {
    *sum = a + b;
    double b_virtual = *sum - a;
    double a_virtual = *sum - b_virtual;
    *error = (a - a_virtual) + (b - b_virtual);
}

// EFT求和
void EFTAdd(double a, double b, double* result) {
    double sum, error;
    TwoSum(a, b, &sum, &error);
    *result = sum + error;
}

// EFT两数之差
void TwoDiff(double a, double b, double* diff, double* error) {
    *diff = a - b;
    double b_virtual = a - *diff;
    double a_virtual = *diff + b_virtual;
    *error = (a - a_virtual) - (b - b_virtual);
}

// EFT减法运算
void EFTSub(double a, double b, double* result) {
    double diff, error;
    TwoDiff(a, b, &diff, &error);
    *result = diff + error;
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
void EFTMul(double a, double b, double* result) {
    double prod, error;
    TwoProd(a, b, &prod, &error);
    *result = prod + error;
}

// EFT除法运算
void EFTDiv(double a, double b, double* result) {
    double q1, r1, q2, r2, q3;

    q1 = a / b;
    r1 = a - q1 * b;
    q2 = r1 / b;
    r2 = r1 - q2 * b;
    q3 = r2 / b;

    *result = q1 + q2 + q3;
}
*/