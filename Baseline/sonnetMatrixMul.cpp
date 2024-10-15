#include <stdio.h>
#include <stdlib.h>
#include "../lib/libeft.h"
#include <time.h>
#include <math.h>

// 矩阵大小
#define SIZE 295

// 定义metadata结构
typedef struct {
    double exact_value;
    double error;
} __eft_metadata_t;

// 定义循环队列
#define QUEUE_SIZE 1024
__eft_metadata_t metadata_queue[QUEUE_SIZE];
int queue_head = 0, queue_tail = 0;

// metadata分配函数
__eft_metadata_t __eft_alloc_metadata() {
    if ((queue_tail + 1) % QUEUE_SIZE == queue_head) {
        // 队列满,重用最旧的metadata
        __eft_metadata_t meta = metadata_queue[queue_head];
        queue_head = (queue_head + 1) % QUEUE_SIZE;
        return meta;
    }
    // 分配新的metadata
    __eft_metadata_t new_meta = {0.0, 0.0};
    metadata_queue[queue_tail] = new_meta;
    queue_tail = (queue_tail + 1) % QUEUE_SIZE;
    return new_meta;
}

// metadata释放函数
void __eft_free_metadata(__eft_metadata_t meta) {
    // 在实际实现中,这里可能不需要真正释放,因为我们使用循环队列重用metadata
}

// EFT乘法操作
void __eft_mul(double* a, double* b, double* result, __eft_metadata_t* meta) {
    *result = *a * *b;
    double a_high, a_low, b_high, b_low;
    const double split = 134217729.0; // 2^27 + 1, 用于浮点数分解

    double temp = *a * split;
    a_high = temp - (temp - *a);
    a_low = *a - a_high;

    temp = *b * split;
    b_high = temp - (temp - *b);
    b_low = *b - b_high;

    meta->exact_value = *result;
    meta->error = ((a_high * b_high - *result) + a_high * b_low + a_low * b_high) + a_low * b_low;
}

// EFT加法操作
void __eft_add(double* a, double* b, double* result, __eft_metadata_t* meta) {
    *result = *a + *b;
    double b_virtual = *result - *a;
    double a_virtual = *result - b_virtual;
    meta->exact_value = *result;
    meta->error = (*a - a_virtual) + (*b - b_virtual);
}

// 错误检查和报告函数
void __eft_check_error(double computed_value, __eft_metadata_t meta, const char* file, int line) {
    double exact_value = meta.exact_value + meta.error;
    double relative_error = fabs((exact_value - computed_value) / exact_value);
    if (relative_error > 1e-8) {
        printf("Error detected at %s:%d - Relative error: %e\n", file, line, relative_error);
    }
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
void MatrixMultiplication(double A[SIZE][SIZE], double B[SIZE][SIZE], double C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            double sum = 0.0;
            __eft_metadata_t sum_meta = __eft_alloc_metadata();
            for (int k = 0; k < SIZE; k++) {
                double product;
                __eft_metadata_t product_meta = __eft_alloc_metadata();
                
                // EFT乘法操作
                __eft_mul(&A[i][k], &B[k][j], &product, &product_meta);
                
                // EFT加法操作
                __eft_add(&sum, &product, &sum, &sum_meta);
                
                // 检查误差
                __eft_check_error(sum, sum_meta, __FILE__, __LINE__);
                
                __eft_free_metadata(product_meta);
            }
            C[i][j] = sum;
            __eft_free_metadata(sum_meta);
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

    printf("EFT Matrix Multiplication Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}

