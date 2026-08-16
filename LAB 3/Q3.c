#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int min;
    int max;
} Pair;

// Divide and Conquer function to find Max and Min
Pair getMinMax(int arr[], int low, int high) {
    Pair result, left, right;

    // Base Case 1: Single element
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    // Base Case 2: Two elements
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }

    // Divide step
    int mid = low + (high - low) / 2;
    left = getMinMax(arr, low, mid);
    right = getMinMax(arr, mid + 1, high);

    // Conquer & Combine step
    result.min = (left.min < right.min) ? left.min : right.min;
    result.max = (left.max > right.max) ? left.max : right.max;

    return result;
}

int main() {
    int choice, n;
    int *arr = NULL;

    printf("========================================\n");
    printf("   Divide & Conquer Max/Min \n");
    printf("========================================\n");
    printf("Select Execution Mode:\n");
    printf("1. Random Simulation (for large benchmark arrays)\n");
    printf("2. Manual Input (custom array size & elements)\n");
    printf("Enter choice (1 or 2): ");
    
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Invalid choice! Exiting...\n");
        return 1;
    }

    if (choice == 1) {
        // Mode 1: Random Simulation
        printf("\nEnter size of array for Random Simulation (e.g., 20000000): ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Invalid array size!\n");
            return 1;
        }

        arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        printf("Generating %d random elements...\n", n);
        srand((unsigned int)time(NULL));
        for (int i = 0; i < n; i++) {
            arr[i] = rand();
        }
    } else {
        // Mode 2: Manual Input
        printf("\nEnter the number of elements (n): ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Invalid array size!\n");
            return 1;
        }

        arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        printf("Enter %d space-separated integer elements:\n", n);
        for (int i = 0; i < n; i++) {
            if (scanf("%d", &arr[i]) != 1) {
                printf("Invalid element input! Exiting...\n");
                free(arr);
                return 1;
            }
        }
    }

    // Measure Execution Time of getMinMax
    clock_t start = clock();
    Pair res = getMinMax(arr, 0, n - 1);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n--- Execution Results ---\n");
    printf("Array Size (n) : %d\n", n);
    printf("Min Element    : %d\n", res.min);
    printf("Max Element    : %d\n", res.max);
    printf("Execution Time : %.6f seconds\n", time_taken);

    free(arr);
    return 0;
}