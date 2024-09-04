#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../lib/libeft.h"

// 莱布尼茨公式计算π (EFT方法)
double EFTLeibnizPi(int n) {
    double sum = 0.0, error = 0.0;
    for (int i = 0; i < n; i++) {
        double term = pow(-1.0, i) / (2.0 * i + 1.0);
        EFTAdd(sum, term, &sum);
    }
    return sum * 4.0;
}

int main() {
    int n = 10000000;  // 计算项数
    clock_t start_time, end_time;

    start_time = clock();
    double pi = EFTLeibnizPi(n);
    end_time = clock();

    printf("EFT Calculated Pi: %.18f\n", pi);
    printf("EFT Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
