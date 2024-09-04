#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>
#include <time.h>

// 生成随机数 (MPFR方法)
void mpfr_rand_double(mpfr_t r) {
    double d = (double)rand() / (double)RAND_MAX;
    mpfr_set_d(r, d, MPFR_RNDN);
}

// Monte Carlo方法计算π (MPFR方法)
void MPFRMonteCarloPi(mpfr_t result, long num_points) {
    long points_in_circle = 0;
    mpfr_t x, y, dist, one;
    mpfr_inits2(256, x, y, dist, one, NULL);
    mpfr_set_d(one, 1.0, MPFR_RNDN);

    for (long i = 0; i < num_points; i++) {
        mpfr_rand_double(x);
        mpfr_rand_double(y);

        mpfr_mul(x, x, x, MPFR_RNDN);
        mpfr_mul(y, y, y, MPFR_RNDN);
        mpfr_add(dist, x, y, MPFR_RNDN);

        if (mpfr_cmp(dist, one) <= 0) {
            points_in_circle++;
        }
    }

    mpfr_set_d(result, 4.0 * (double)points_in_circle / (double)num_points, MPFR_RNDN);

    mpfr_clears(x, y, dist, one, NULL);
}

int main() {
    srand(time(NULL));
    long num_points = 10000000;
    mpfr_t pi;
    mpfr_init2(pi, 256);

    clock_t start_time, end_time;

    start_time = clock();
    MPFRMonteCarloPi(pi, num_points);
    end_time = clock();

    printf("MPFR Calculated Pi: ");
    mpfr_out_str(stdout, 10, 18, pi, MPFR_RNDN);
    printf("\n");
    printf("MPFR Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    mpfr_clear(pi);

    return 0;
}
