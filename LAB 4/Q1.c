#include <stdio.h>
#include <string.h>

struct Item {
    int number;
    char colour[10];
};

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item a[n];
    struct Item red[n], blue[n], yellow[n];

    int r = 0, b = 0, y = 0;

    printf("Enter number and colour (Red/Blue/Yellow):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %s", &a[i].number, a[i].colour);

        if (strcmp(a[i].colour, "Red") == 0 ||
            strcmp(a[i].colour, "red") == 0) {
            red[r++] = a[i];
        }
        else if (strcmp(a[i].colour, "Blue") == 0 ||
                 strcmp(a[i].colour, "blue") == 0) {
            blue[b++] = a[i];
        }
        else if (strcmp(a[i].colour, "Yellow") == 0 ||
                 strcmp(a[i].colour, "yellow") == 0) {
            yellow[y++] = a[i];
        }
    }

    int k = 0;

    // Copy red items
    for (int i = 0; i < r; i++)
        a[k++] = red[i];

    // Copy blue items
    for (int i = 0; i < b; i++)
        a[k++] = blue[i];

    // Copy yellow items
    for (int i = 0; i < y; i++)
        a[k++] = yellow[i];

    printf("\nSorted items by colour:\n");

    for (int i = 0; i < n; i++) {
        printf("(%d, %s)\n", a[i].number, a[i].colour);
    }

    return 0;
}