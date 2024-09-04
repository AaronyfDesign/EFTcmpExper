#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../lib/libeft.h"

// 生成随机数
double rand_double() {
    return (double)rand() / (double)RAND_MAX;
}


// Monte Carlo方法计算π (EFT方法)
double EFTMonteCarloPi(long num_points) {
    long points_in_circle = 0;
    for (long i = 0; i < num_points; i++) {
        double x = rand_double();
        double y = rand_double();
        double dist;
        EFTMul(x, x, &x);
        EFTMul(y, y, &y);
        EFTAdd(x, y, &dist);
        //dist = x * x + y * y;

        if (dist <= 1.0) {
            double temp;
            EFTAdd((double)points_in_circle, 1.0, &temp);
            points_in_circle = (long)temp;
        }
    }
    return 4.0 * (double)points_in_circle / (double)num_points;
}

int main() {
    srand(time(NULL));
    long num_points = 10000000;

    clock_t start_time, end_time;

    start_time = clock();
    double pi = EFTMonteCarloPi(num_points);
    end_time = clock();

    printf("EFT Calculated Pi: %.18f\n", pi);
    printf("EFT Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
