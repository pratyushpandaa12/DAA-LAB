#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x) return mid;
        if (arr[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int ternarySearch(int arr[], int l, int r, int x) {
    while (r >= l) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        if (arr[mid1] == x) return mid1;
        if (arr[mid2] == x) return mid2;

        if (x < arr[mid1]) {
            r = mid1 - 1;
        } 
        else if (x > arr[mid2]) {
            l = mid2 + 1;
        } 
        else {
            l = mid1 + 1;
            r = mid2 - 1;
        }
    }
    return -1;
}

int main() {
    int n = 50000000; // 50 million elements
    int *arr = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
    }

    int target = 87654321; // Target element
    int iterations = 10000000; // 10 million lookups for measurable timing

    // Measure Binary Search
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        volatile int res = binarySearch(arr, 0, n - 1, target);
    }
    clock_t end = clock();
    double binaryTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Measure Ternary Search
    start = clock();
    for (int i = 0; i < iterations; i++) {
        volatile int res = ternarySearch(arr, 0, n - 1, target);
    }
    end = clock();
    double ternaryTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("--- Execution Results ---\n");
    printf("Array Size: %d elements\n", n);
    printf("Total Searches Executed: %d\n", iterations);
    printf("Binary Search Time : %.6f seconds\n", binaryTime);
    printf("Ternary Search Time: %.6f seconds\n", ternaryTime);

    free(arr);
    return 0;
}