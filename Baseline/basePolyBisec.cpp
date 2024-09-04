#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../lib/libeft.h"

// 多项式函数 f(x) = x^5 - 5x^4 + 10x^3 - 10x^2 + 5x - 1
double polynomial(double x) {
    return pow(x, 5) - 5 * pow(x, 4) + 10 * pow(x, 3) - 10 * pow(x, 2) + 5 * x - 1;
}
double moveaPoly(double x) {
    double a = 0, tmp; // 原函数向右平移a个单位
    //EFTAdd(x, a, &tmp);
    tmp = x + a;
    return polynomial(tmp);
}

// 二分法求根 (EFT方法)
double EFTBisection(double (*func)(double), double a, double b, double tol) {
    double mid, f_a, f_mid;

    while ((b - a) > tol) {
        //mid = (a + b) / 2.0;
        EFTAdd(a, b, &mid);
        mid /= 2.0;
        f_a = func(a);
        f_mid = func(mid);
        //printf("%lf %lf \n", f_a, f_mid);

        if (f_a * f_mid < 0) {
            b = mid;
        } else {
            a = mid;
        }
    }
    return (a + b) / 2.0;
}

int main() {
    double a = 0.2, b = 1.5, tol = 1e-18;
    clock_t start_time, end_time;

    start_time = clock();
    double root = EFTBisection(polynomial, a, b, tol);
    //double root = EFTBisection(moveaPoly, a, b, tol);
    end_time = clock();

    printf("BASE Root: %.18f\n", root);
    printf("BASE Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
