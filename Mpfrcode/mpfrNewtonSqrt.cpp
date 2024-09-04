#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>
#include <time.h>

void MPFRNewtonSqrt(mpfr_t result, mpfr_t num, int iterations) {
    mpfr_t x, tmp1, tmp2;
    mpfr_init2(x, mpfr_get_prec(num));
    mpfr_init2(tmp1, mpfr_get_prec(num));
    mpfr_init2(tmp2, mpfr_get_prec(num));

    // x = num / 2.0
    mpfr_div_ui(x, num, 2, MPFR_RNDN);

    for (int i = 0; i < iterations; i++) {
        mpfr_mul(tmp1, x, x, MPFR_RNDN);    // tmp1 = x * x
        mpfr_div(tmp2, num, x, MPFR_RNDN); // tmp2 = num / x
        mpfr_add(tmp1, x, tmp2, MPFR_RNDN);  // tmp1 = x + tmp2
        mpfr_div_ui(x, tmp1, 2, MPFR_RNDN);  // x = tmp1 / 2
    }

    mpfr_set(result, x, MPFR_RNDN);

    mpfr_clear(x);
    mpfr_clear(tmp1);
    mpfr_clear(tmp2);
}

int main() {
    mpfr_t num, result;
    mpfr_init2(num, 256);  // 设置高精度
    mpfr_init2(result, 256);

    mpfr_set_d(num, 1e10, MPFR_RNDN);  // 复杂初始条件

    int iterations = 100000;

    clock_t start_time = clock();
    MPFRNewtonSqrt(result, num, iterations);
    clock_t end_time = clock();

    printf("MPFR Result: ");
    mpfr_out_str(stdout, 10, 15, result, MPFR_RNDN);
    printf("\n");
    printf("MPFR Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // 清除MPFR变量
    mpfr_clear(num);
    mpfr_clear(result);

    return 0;
}
