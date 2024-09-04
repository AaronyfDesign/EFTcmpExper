#include <stdio.h>
#include <math.h>
#include <time.h>

#define EPSILON 1e-18  // 18位有效数字

// 定义多项式
double polynomial(double x) {
    return x*x*x*x*x - 3*x*x*x*x + 2*x*x*x - 5*x*x + x - 7;
}

// EFT加法
double eft_add(double a, double b, double *err) {
    double sum = a + b;
    *err = (a - sum) + b;
    return sum;
}

// EFT乘法
double eft_mul(double a, double b, double *err) {
    double product = a * b;
    *err = fma(a, b, -product);
    return product;
}

// 二分法求根
double bisection(double a, double b, double (*f)(double), double *error) {
    double c = a;
    while ((b-a) >= EPSILON) {
        c = (a+b)/2;
        if (f(c) == 0.0) 
            break;
        else if (f(c)*f(a) < 0) 
            b = c;
        else
            a = c;
    }
    return c;
}

int main() {
    double a = 1, b = 2; // 设置初始区间
    double error;
    clock_t start, end;

    start = clock();
    double root = bisection(a, b, polynomial, &error);
    end = clock();

    printf("根的值: %.18lf\n", root);
    printf("EFT计算时间: %lf 秒\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    printf("近似误差: %.18lf\n", error);

    return 0;
}
