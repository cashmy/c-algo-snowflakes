#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: This approach follows a design pattern in which the comparative array is transversed in both directions.
//       Binary Search Trees are an example of a "Tranvserse in Both Directions" design pattern.


// initial function to determine concept of unique snowflakes
// using a simple array
void find_identical(int values[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {

         // Start at the next element, otherwise we are comparing the same element
         // and will get a false positive.
        for (j = i + 1; j < n; j++) {
            if (values[i] == values[j]) {
                printf("Twin integers found.\n");
                return;
            }
        }

    }
    printf("No two integers are the identical.\n");
}


// As the std sizeOf operation on an array is not supported in C, and must be calculated
// manually, we will use a hard-coded value for now (in order to optimize processing time).
int main(void) {
    int a[6] = {1, 2, 3, 4, 1, 6};
    find_identical(a, 6);
    return 0;
}