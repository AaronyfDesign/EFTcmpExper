/*
// EFT两数之和
void TwoSum(double a, double b, double* sum, double* error);

// EFT加法运算
void EFTAdd(double a, double b, double* result);

// EFT两数之差
void TwoDiff(double a, double b, double* diff, double* error);

// EFT减法运算
void EFTSub(double a, double b, double* result);

// EFT两数之积
void TwoProd(double a, double b, double* prod, double* error);

// EFT乘法运算
void EFTMul(double a, double b, double* result);

// EFT除法运算
void EFTDiv(double a, double b, double* result);
*/


// EFT两数之和
void TwoSum(double a, double b, double* sum, double* error) {
    *sum = a + b;
    double b_virtual = *sum - a;
    double a_virtual = *sum - b_virtual;
    *error = (a - a_virtual) + (b - b_virtual);
}

// EFT求和
void EFTAdd(double a, double b, double* result) {
    double sum, error;
    TwoSum(a, b, &sum, &error);
    *result = sum + error;
}

// EFT两数之差
void TwoDiff(double a, double b, double* diff, double* error) {
    *diff = a - b;
    double b_virtual = a - *diff;
    double a_virtual = *diff + b_virtual;
    *error = (a - a_virtual) - (b - b_virtual);
}

// EFT减法运算
void EFTSub(double a, double b, double* result) {
    double diff, error;
    TwoDiff(a, b, &diff, &error);
    *result = diff + error;
}

// EFT两数之积
void TwoProd(double a, double b, double* prod, double* error) {
    *prod = a * b;
    double a_high, a_low, b_high, b_low;

    const double split = 134217729.0; // 2^27 + 1, 用于浮点数分解

    a_high = a * split;
    a_low = a - a_high;
    a_high = a_high + a_low - a;
    a_low = a - a_high;

    b_high = b * split;
    b_low = b - b_high;
    b_high = b_high + b_low - b;
    b_low = b - b_high;

    *error = ((a_high * b_high - *prod) + a_high * b_low + a_low * b_high) + a_low * b_low;
}

// EFT乘法运算
void EFTMul(double a, double b, double* result) {
    double prod, error;
    TwoProd(a, b, &prod, &error);
    *result = prod + error;
}

// EFT除法运算
void EFTDiv(double a, double b, double* result) {
    double q1, r1, q2, r2, q3;

    q1 = a / b;
    r1 = a - q1 * b;
    q2 = r1 / b;
    r2 = r1 - q2 * b;
    q3 = r2 / b;

    *result = q1 + q2 + q3;
}
