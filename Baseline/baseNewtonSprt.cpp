#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// 牛顿迭代法求平方根
double NewtonSqrt(double num, int iterations) {
    double x = num / 2.0;
    int iend;
    for (int i = 0; i < iterations; i++) {
        double approx, error, diff, sum;
        //EFTAdd(x,num/x, &sum);
        sum = x + num/x;
        x = sum / 2.0;
    }
    return x;
}

int main() {
    double num = 1e10;  // 复杂初始条件
    int iterations = 100000;

    clock_t start_time = clock();
    double result = NewtonSqrt(num, iterations);
    clock_t end_time = clock();

    printf("BASE Result: %.15f\n", result);
    printf("BASE Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
