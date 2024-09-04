#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>
#include <time.h>

// 多项式函数 f(x) = x^5 - 5x^4 + 10x^3 - 10x^2 + 5x - 1
void mpfr_polynomial(mpfr_t result, mpfr_t x) {
    mpfr_t tmp;
    mpfr_init2(tmp, mpfr_get_prec(x));

    mpfr_pow_ui(result, x, 5, MPFR_RNDN);
    mpfr_pow_ui(tmp, x, 4, MPFR_RNDN);
    mpfr_mul_ui(tmp, tmp, 5, MPFR_RNDN);
    mpfr_sub(result, result, tmp, MPFR_RNDN);

    mpfr_pow_ui(tmp, x, 3, MPFR_RNDN);
    mpfr_mul_ui(tmp, tmp, 10, MPFR_RNDN);
    mpfr_add(result, result, tmp, MPFR_RNDN);

    mpfr_pow_ui(tmp, x, 2, MPFR_RNDN);
    mpfr_mul_ui(tmp, tmp, 10, MPFR_RNDN);
    mpfr_sub(result, result, tmp, MPFR_RNDN);

    mpfr_mul_ui(tmp, x, 5, MPFR_RNDN);
    mpfr_add(result, result, tmp, MPFR_RNDN);

    mpfr_sub_ui(result, result, 1, MPFR_RNDN);

    mpfr_clear(tmp);
}

// 二分法求根 (MPFR方法)
void MPFRBisection(mpfr_t root, void (*func)(mpfr_t, mpfr_t), mpfr_t a, mpfr_t b, mpfr_t tol) {
    mpfr_t mid, f_a, f_mid;
    mpfr_inits2(256, mid, f_a, f_mid, NULL);

    while (mpfr_cmp(a, b) < 0 && mpfr_sub(mid, b, a, MPFR_RNDN), mpfr_cmp(mid, tol) > 0) {
        mpfr_add(mid, a, b, MPFR_RNDN);
        mpfr_div_ui(mid, mid, 2, MPFR_RNDN);

        func(f_a, a);
        func(f_mid, mid);

        if (mpfr_sgn(f_a) * mpfr_sgn(f_mid) < 0) {
            mpfr_set(b, mid, MPFR_RNDN);
        } else {
            mpfr_set(a, mid, MPFR_RNDN);
        }
    }
    mpfr_add(root, a, b, MPFR_RNDN);
    mpfr_div_ui(root, root, 2, MPFR_RNDN);

    mpfr_clears(mid, f_a, f_mid, NULL);
}

int main() {
    mpfr_t a, b, tol, root;
    mpfr_inits2(256, a, b, tol, root, NULL);

    mpfr_set_d(a, 0.2, MPFR_RNDN);
    mpfr_set_d(b, 1.5, MPFR_RNDN);
    mpfr_set_d(tol, 1e-18, MPFR_RNDN);

    clock_t start_time, end_time;

    start_time = clock();
    MPFRBisection(root, mpfr_polynomial, a, b, tol);
    end_time = clock();

    printf("MPFR Root: ");
    mpfr_out_str(stdout, 10, 18, root, MPFR_RNDN);
    printf("\n");
    printf("MPFR Execution Time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    mpfr_clears(a, b, tol, root, NULL);

    return 0;
}
