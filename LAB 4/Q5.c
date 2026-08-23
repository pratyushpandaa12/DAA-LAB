#include <stdio.h>
#include <stdlib.h>

struct Interval {
    int start;
    int end;
};

int compare(const void *a, const void *b) {
    struct Interval *i1 = (struct Interval *)a;
    struct Interval *i2 = (struct Interval *)b;

    return i1->start - i2->start;
}

int main() {
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Interval intervals[n];
    struct Interval result[n];

    printf("Enter the intervals:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d",
              &intervals[i].start,
              &intervals[i].end);
    }

    // Sort intervals by starting point
    qsort(intervals, n, sizeof(struct Interval), compare);

    int count = 0;

    // Start with the first interval
    int currentStart = intervals[0].start;
    int currentEnd = intervals[0].end;

    for (int i = 1; i < n; i++) {

        // Intervals overlap
        if (intervals[i].start <= currentEnd) {

            if (intervals[i].end > currentEnd)
                currentEnd = intervals[i].end;
        }

        // No overlap
        else {
            result[count].start = currentStart;
            result[count].end = currentEnd;
            count++;

            currentStart = intervals[i].start;
            currentEnd = intervals[i].end;
        }
    }

    // Add the last interval
    result[count].start = currentStart;
    result[count].end = currentEnd;
    count++;

    printf("\nMerged intervals:\n");

    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n",
               result[i].start,
               result[i].end);
    }

    return 0;
}