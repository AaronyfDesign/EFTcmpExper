#include <iostream>
#include <mpfr.h>
#include <time.h>

#define PRECISION 256  // 设置256位精度，保证18位有效数字

// 定义多项式
void polynomial(mpfr_t result, mpfr_t x) {
    mpfr_t term, temp;
    mpfr_inits(term, temp, NULL);

    // result = x^5 - 3x^4 + 2x^3 - 5x^2 + x - 7
    mpfr_pow_ui(term, x, 5, MPFR_RNDN);
    mpfr_set(result, term, MPFR_RNDN);

    mpfr_pow_ui(term, x, 4, MPFR_RNDN);
    mpfr_mul_si(term, term, 3, MPFR_RNDN);
    mpfr_sub(result, result, term, MPFR_RNDN);

    mpfr_pow_ui(term, x, 3, MPFR_RNDN);
    mpfr_mul_si(term, term, 2, MPFR_RNDN);
    mpfr_add(result, result, term, MPFR_RNDN);

    mpfr_pow_ui(term, x, 2, MPFR_RNDN);
    mpfr_mul_si(term, term, 5, MPFR_RNDN);
    mpfr_sub(result, result, term, MPFR_RNDN);

    mpfr_add(result, result, x, MPFR_RNDN);
    mpfr_sub_si(result, result, 7, MPFR_RNDN);

    mpfr_clears(term, temp, NULL);
}

// 二分法求根
void bisection(mpfr_t root, mpfr_t a, mpfr_t b, mpfr_prec_t prec) {
    mpfr_t f_a, f_b, f_mid, mid, temp;
    mpfr_inits(f_a, f_b, f_mid, mid, temp, NULL);

    while (mpfr_cmp(a, b) < 0) {
        mpfr_add(mid, a, b, MPFR_RNDN);
        mpfr_div_ui(mid, mid, 2, MPFR_RNDN);

        polynomial(f_mid, mid);

        if (mpfr_zero_p(f_mid)) {
            mpfr_set(root, mid, MPFR_RNDN);
            break;
        }

        polynomial(f_a, a);
        if (mpfr_sgn(f_mid) * mpfr_sgn(f_a) < 0) {
            mpfr_set(b, mid, MPFR_RNDN);
        } else {
            mpfr_set(a, mid, MPFR_RNDN);
        }

        mpfr_sub(temp, b, a, MPFR_RNDN);
        if (mpfr_cmp_d(temp, pow(10, -18)) < 0) {
            mpfr_set(root, mid, MPFR_RNDN);
            break;
        }
    }

    mpfr_clears(f_a, f_b, f_mid, mid, temp, NULL);
}

int main() {
    mpfr_set_default_prec(PRECISION);

    mpfr_t a, b, root;
    mpfr_inits(a, b, root, NULL);

    mpfr_set_d(a, 1.0, MPFR_RNDN);
    mpfr_set_d(b, 2.0, MPFR_RNDN);

    clock_t start, end;

    start = clock();
    bisection(root, a, b, PRECISION);
    end = clock();

    printf("根的值: ");
    mpfr_printf("%.18Rf\n", root);
    printf("MPFR计算时间: %lf 秒\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    mpfr_clears(a, b, root, NULL);

    return 0;
}
