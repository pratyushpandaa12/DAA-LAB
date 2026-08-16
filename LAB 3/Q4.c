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
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int **A11 = allocateMatrix(k), **A12 = allocateMatrix(k), **A21 = allocateMatrix(k), **A22 = allocateMatrix(k);
    int **B11 = allocateMatrix(k), **B12 = allocateMatrix(k), **B21 = allocateMatrix(k), **B22 = allocateMatrix(k);
    int **C11 = allocateMatrix(k), **C12 = allocateMatrix(k), **C21 = allocateMatrix(k), **C22 = allocateMatrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];         A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];     A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];         B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];     B22[i][j] = B[i + k][j + k];
        }
    }

    int **P1 = allocateMatrix(k), **P2 = allocateMatrix(k), **P3 = allocateMatrix(k), **P4 = allocateMatrix(k);
    int **P5 = allocateMatrix(k), **P6 = allocateMatrix(k), **P7 = allocateMatrix(k);
    int **t1 = allocateMatrix(k), **t2 = allocateMatrix(k);

    // P1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, t1, k); add(B11, B22, t2, k); strassen(t1, t2, P1, k);
    // P2 = (A21 + A22) * B11
    add(A21, A22, t1, k); strassen(t1, B11, P2, k);
    // P3 = A11 * (B12 - B22)
    sub(B12, B22, t2, k); strassen(A11, t2, P3, k);
    // P4 = A22 * (B21 - B11)
    sub(B21, B11, t2, k); strassen(A22, t2, P4, k);
    // P5 = (A11 + A12) * B22
    add(A11, A12, t1, k); strassen(t1, B22, P5, k);
    // P6 = (A21 - A11) * (B11 + B12)
    sub(A21, A11, t1, k); add(B11, B12, t2, k); strassen(t1, t2, P6, k);
    // P7 = (A12 - A22) * (B21 + B22)
    sub(A12, A22, t1, k); add(B21, B22, t2, k); strassen(t1, t2, P7, k);

    // C11 = P1 + P4 - P5 + P7
    add(P1, P4, t1, k); sub(t1, P5, t2, k); add(t2, P7, C11, k);
    // C12 = P3 + P5
    add(P3, P5, C12, k);
    // C21 = P2 + P4
    add(P2, P4, C21, k);
    // C22 = P1 - P2 + P3 + P6
    sub(P1, P2, t1, k); add(t1, P3, t2, k); add(t2, P6, C22, k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C11[i][j]; C[i][j + k]     = C12[i][j];
            C[i + k][j]     = C21[i][j]; C[i + k][j + k] = C22[i][j];
        }
    }

    freeMatrix(A11, k); freeMatrix(A12, k); freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k); freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(C11, k); freeMatrix(C12, k); freeMatrix(C21, k); freeMatrix(C22, k);
    freeMatrix(P1, k);  freeMatrix(P2, k);  freeMatrix(P3, k);  freeMatrix(P4, k);
    freeMatrix(P5, k);  freeMatrix(P6, k);  freeMatrix(P7, k);
    freeMatrix(t1, k);  freeMatrix(t2, k);
}

int main() {
    int n = 128; // Power of 2 matrix size
    int **A = allocateMatrix(n), **B = allocateMatrix(n), **C = allocateMatrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

    clock_t start = clock();
    strassen(A, B, C, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Execution Results ---\n");
    printf("Matrix Size: %dx%d\n", n, n);
    printf("Strassen Execution Time: %.6f seconds\n", time_taken);

    freeMatrix(A, n); freeMatrix(B, n); freeMatrix(C, n);
    return 0;
}