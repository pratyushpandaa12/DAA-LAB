#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Helper to sum array segment (simulates balance scale)
double sumWeights(double coins[], int l, int r) {
    double total = 0;
    for (int i = l; i <= r; i++) {
        total += coins[i];
    }
    return total;
}

int findDefectiveCoin(double coins[], int l, int r) {
    if (l == r) return l; // Single coin remaining

    int n = r - l + 1;
    int half = n / 2;

    int left_start = l;
    int left_end = l + half - 1;
    int right_start = l + half;
    int right_end = l + 2 * half - 1;

    double leftWeight = sumWeights(coins, left_start, left_end);
    double rightWeight = sumWeights(coins, right_start, right_end);

    if (leftWeight < rightWeight) {
        return findDefectiveCoin(coins, left_start, left_end);
    } else if (rightWeight < leftWeight) {
        return findDefectiveCoin(coins, right_start, right_end);
    } else {
        // Both halves equal: if n is odd, defective coin is the extra one
        if (n % 2 != 0) {
            return r;
        }
        return -1; // All coins perfect
    }
}

int main() {
    int n = 10000000; // 10 million coins
    double *coins = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) coins[i] = 10.0; // Normal weight
    int defective_index = 7432198;
    coins[defective_index] = 9.5; // Lighter coin

    clock_t start = clock();
    int idx = findDefectiveCoin(coins, 0, n - 1);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Execution Results ---\n");
    if (idx != -1) {
        printf("Defective coin found at index: %d\n", idx);
    } 
    else {
        printf("No defective coin found. All coins are perfect.\n");
    }
    printf("Execution Time: %.6f seconds\n", time_taken);

    free(coins);
    return 0;
}