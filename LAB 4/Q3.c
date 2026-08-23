#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int binarySearch(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return 1;

        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

/*
   Recursively selects k-1 elements.
   sum = sum of currently selected elements
*/
int findKSum(int arr[], int n, int k, int T,
             int start, int depth, int sum) {

    // Select k-1 elements
    if (depth == k - 1) {
        int target = T - sum;

        if (binarySearch(arr, n, target))
            return 1;

        return 0;
    }

    for (int i = start; i < n; i++) {

        if (findKSum(arr, n, k, T,
                     i + 1, depth + 1,
                     sum + arr[i])) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int n, k, T;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int S[n];

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S[i]);

    printf("Enter value of k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    if (k > n || k < 2) {
        printf("Invalid value of k.\n");
        return 0;
    }

    // Sort the set
    qsort(S, n, sizeof(int), compare);

    if (findKSum(S, n, k, T, 0, 0, 0))
        printf("\nYes, %d elements add up to %d.\n", k, T);
    else
        printf("\nNo, %d elements add up to %d.\n", k, T);

    return 0;
}