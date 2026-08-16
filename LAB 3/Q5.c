#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** allocateMatrix(int n) {
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) mat[i] = (int *)calloc(n, sizeof(int));
    return mat;
}

void freeMatrix(int **mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

void add(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) C[i][j] = A[i][j] + B[i][j];
}

void sub(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) C[i][j] = A[i][j] - B[i][j];
}

// Special D&C Multiplication: T(n) = 2 T(n/2) + O(n^2) => O(n^2)
void multiplySpecial(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int **A1 = allocateMatrix(k), **A2 = allocateMatrix(k);
    int **B1 = allocateMatrix(k), **B2 = allocateMatrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];
            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    int **sumA = allocateMatrix(k), **sumB = allocateMatrix(k);
    int **diffA = allocateMatrix(k), **diffB = allocateMatrix(k);
    int **P1 = allocateMatrix(k), **P2 = allocateMatrix(k);

    add(A1, A2, sumA, k); add(B1, B2, sumB, k);
    sub(A1, A2, diffA, k); sub(B1, B2, diffB, k);

    // Only 2 recursive calls
    multiplySpecial(sumA, sumB, P1, k);
    multiplySpecial(diffA, diffB, P2, k);

    int **C1 = allocateMatrix(k), **C2 = allocateMatrix(k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C1[i][j] = (P1[i][j] + P2[i][j]) / 2;
            C2[i][j] = (P1[i][j] - P2[i][j]) / 2;
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C1[i][j]; C[i][j + k]     = C2[i][j];
            C[i + k][j]     = C2[i][j]; C[i + k][j + k] = C1[i][j];
        }
    }

    freeMatrix(A1, k); freeMatrix(A2, k); freeMatrix(B1, k); freeMatrix(B2, k);
    freeMatrix(sumA, k); freeMatrix(sumB, k); freeMatrix(diffA, k); freeMatrix(diffB, k);
    freeMatrix(P1, k); freeMatrix(P2, k); freeMatrix(C1, k); freeMatrix(C2, k);
}

int main() {
    int n = 256; // Matrix size
    int **A = allocateMatrix(n), **B = allocateMatrix(n), **C = allocateMatrix(n);

    // Fill symmetric pattern
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n/2; j++) {
            A[i][j] = A[i+n/2][j+n/2] = rand() % 10;
            A[i][j+n/2] = A[i+n/2][j] = rand() % 10;
            B[i][j] = B[i+n/2][j+n/2] = rand() % 10;
            B[i][j+n/2] = B[i+n/2][j] = rand() % 10;
        }
    }

    clock_t start = clock();
    multiplySpecial(A, B, C, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Execution Results ---\n");
    printf("Matrix Size: %dx%d\n", n, n);
    printf("Special Pattern Matrix Multiplication Time: %.6f seconds\n", time_taken);

    freeMatrix(A, n); freeMatrix(B, n); freeMatrix(C, n);
    return 0;
}