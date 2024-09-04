#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>
#include <math.h>
#include <time.h>

// 莱布尼茨公式计算π (MPFR方法)
void MPFRLeibnizPi(mpfr_t result, int n) {
    mpfr_t term, sum, factor;
    mpfr_inits2(256, term, sum, factor, NULL);

    mpfr_set_d(sum, 0.0, MPFR_RNDN);
    for (int i = 0; i < n; i++) {
        mpfr_set_d(factor, pow(-1.0, i), MPFR_RNDN);
        mpfr_div_ui(term, factor, 2 * i + 1, MPFR_RNDN);
        mpfr_add(sum, sum, term, MPFR_RNDN);
    }
    mpfr_mul_ui(result, sum, 4, MPFR_RNDN);

    mpfr_clears(term, sum, factor, NULL);
}

int main() {
    int n = 10000000;  // 计算项数
    mpfr_t pi;
    mpfr_init2(pi, 256);  // 设置高精度

    clock_t start_time, end_time;

    start_time = clock();
    MPFRLeibnizPi(pi, n);
    end_time = clock();

    printf("MPFR Calculated Pi: ");
    mpfr_out_str(stdout, 10, 18, pi, MPFR_RNDN);
    printf("\n");
    printf("MPFR Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    mpfr_clear(pi);

    return 0;
}
