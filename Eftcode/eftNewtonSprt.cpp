#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 拆分浮点数
void TwoSum(double a, double b, double* sum, double* error) {
    *sum = a + b;
    double b_virtual = *sum - a;
    double a_virtual = *sum - b_virtual;
    *error = (a - a_virtual) + (b - b_virtual);
}

// EFT加法
void EFTAdd(double a, double b, double* result) {
    double sum, error;
    TwoSum(a, b, &sum, &error);
    *result = sum + error;
}

// EFT牛顿迭代法求平方根
double EFTNewtonSqrt(double num, int iterations) {
    double x = num / 2.0;
    int iend;
    for (int i = 0; i < iterations; i++) {
        double approx, error, diff, sum;
        /*
        EFTAdd(x, x, &approx);
        diff = num / approx;
        EFTAdd(approx, diff, &sum);
        */
        EFTAdd(x,num/x, &sum);
        x = sum / 2.0;
        /*
        if (x * x <= num){
            iend = i;
            break;
        }
        */
    }
    //printf("Iteration end at NO.%d\n", iend + 1);
    return x;
}

int main() {
    double num = 1e10;  // 复杂初始条件
    int iterations = 100000;

    clock_t start_time = clock();
    double result = EFTNewtonSqrt(num, iterations);
    clock_t end_time = clock();

    printf("EFT Result: %.15f\n", result);
    printf("EFT Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
