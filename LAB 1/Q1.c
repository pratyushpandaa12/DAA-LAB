
#include <stdio.h>
#include <math.h>

int main(void) {
    long long ns[] = {10, 100, 500, 1000, 5000, 10000, 50000};
    int count = sizeof(ns) / sizeof(ns[0]);

    printf("%-8s %-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n",
           "n", "1/n", "log2(n)", "12*sqrt(n)", "50*n^0.5", "n^0.51",
           "2^32*n", "n*log2(n)", "n^2-324", "100n^2+6n", "2n^3", "n^(log2 n)");

    for (int i = 0; i < count; i++) {
        double n = (double) ns[i];
        double inv_n      = 1.0 / n;
        double log2n      = log2(n);
        double twelve_sqrt= 12.0 * sqrt(n);
        double fifty_sqrt = 50.0 * pow(n, 0.5);
        double n051       = pow(n, 0.51);
        double huge_lin    = pow(2.0, 32.0) * n;
        double nlogn       = n * log2(n);
        double quad1       = n * n - 324.0;
        double quad2       = 100.0 * n * n + 6.0 * n;
        double cubic       = 2.0 * n * n * n;
        double n_log_n_pow = pow(n, log2(n));   

        printf("%-8lld %-12.3e %-12.3e %-12.3e %-12.3e %-12.3e %-12.3e %-12.3e %-12.3e %-12.3e %-12.3e %-12.3e\n",
               ns[i], inv_n, log2n, twelve_sqrt, fifty_sqrt, n051,
               huge_lin, nlogn, quad1, quad2, cubic, n_log_n_pow);
    }

    /* 3^n grows too fast to tabulate alongside the rest without overflow,
       so we show it separately for small n only. */
    printf("\n3^n (shown separately, grows fastest of all):\n");
    for (int i = 1; i <= 20; i += 4) {
        printf("  n = %2d -> 3^n = %.3e\n", i, pow(3.0, (double) i));
    }

    printf("\nTheoretical increasing order of growth (for sufficiently large n):\n");
    printf("1/n  <  log2(n)  <  12*sqrt(n)  <  50*n^0.5  <  n^0.51  <  "
           "2^32*n  <  n*log2(n)  <  (n^2-324)  <  (100n^2+6n)  <  "
           "2n^3  <  n^(log2 n)  <  3^n\n");

    printf("\nNotes:\n");
    printf(" - 12*sqrt(n) and 50*n^0.5 are the SAME asymptotic class (Theta(sqrt n));\n");
    printf("   12*sqrt(n) is smaller only because of the constant (12 < 50).\n");
    printf(" - n^2-324 and 100n^2+6n are the SAME class (Theta(n^2));\n");
    printf("   n^2-324 is smaller only because of the constant (1 < 100).\n");
    printf(" - 2^32*n LOOKS huge for small n (constant ~4.29e9) but it is still only\n");
    printf("   linear in n, so n*log2(n) eventually overtakes it for large enough n.\n");
    printf(" - n^(log2 n) is 'superpolynomial': it beats every fixed power of n\n");
    printf("   (n^2, n^3, ...) eventually, but is still slower than 3^n.\n");
    return 0;
}