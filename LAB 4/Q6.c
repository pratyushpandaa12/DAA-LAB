#include <stdio.h>
#include <stdlib.h>

struct Event {
    int position;
    int type;       // +1 = start, -1 = end
};

int compare(const void *a, const void *b) {
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    if (e1->position != e2->position)
        return e1->position - e2->position;

    // Start event before end event
    return e2->type - e1->type;
}

int main() {
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    printf("Enter left and right endpoints:\n");

    for (int i = 0; i < n; i++) {
        int l, r;

        scanf("%d %d", &l, &r);

        events[2 * i].position = l;
        events[2 * i].type = 1;

        events[2 * i + 1].position = r;
        events[2 * i + 1].type = -1;
    }

    // Sort events
    qsort(events, 2 * n, sizeof(struct Event), compare);

    int current = 0;
    int maximum = 0;
    int point = 0;

    // Sweep through all events
    for (int i = 0; i < 2 * n; i++) {

        current += events[i].type;

        if (current > maximum) {
            maximum = current;
            point = events[i].position;
        }
    }

    printf("\nPoint with maximum overlap = %d\n", point);
    printf("Maximum number of intervals = %d\n", maximum);

    return 0;
}