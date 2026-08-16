#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = A[i];
            A[i] = A[min_idx];
            A[min_idx] = temp;
        }
    }
}

int main() {
    int n = 30000; // Array size
    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }

    clock_t start = clock();
    selectionSort(arr, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Execution Results ---\n");
    printf("Array Size: %d elements\n", n);
    printf("Selection Sort Execution Time: %.6f seconds\n", time_taken);

    free(arr);
    return 0;
}