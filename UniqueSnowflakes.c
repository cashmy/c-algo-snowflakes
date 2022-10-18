#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: This approach follows a design pattern in which the comparative array is transversed in both directions.
//       Binary Search Trees are an example of a "Tranvserse in Both Directions" design pattern.


// initial function to determine concept of unique snowflakes
// using a simple array
// void find_identical(int values[], int n) {
//     int i, j;
//     for (i = 0; i < n; i++) {

         // Start at the next element, otherwise we are comparing the same element
         // and will get a false positive.
//         for (j = i + 1; j < n; j++) {
//             if (values[i] == values[j]) {
//                 printf("Twin integers found.\n");
//                 return;
//             }
//         }

//     }
//     printf("No two integers are the identical.\n");
// }


// Transverse "RIGHT" to determine match.
// If match is found, return 1, otherwise return 0. (Boolean)
int find_right(int flake1[], int flake2[], int start) {
    int offset;
    for (offset = 0; offset < 6; offset++) {
        // Using modulus to wrap around the array.
        if (flake1[offset] != flake2[(start + offset) % 6]) {
            return 0;
        }
    }
    return 1;
}

// Transverse "LEFT" to determine match.
// If match is found, return 1, otherwise return 0. (Boolean)
// Modulus will NOT work here, because we are going backwards.
int find_left(int flake1[], int flake2[], int start) {
    int offset, flake2_index;
    for (offset = 0; offset < 6; offset++) {
        flake2_index = start - offset;
        if (flake2_index < 0) {
            flake2_index += 6;
        }
        if (flake1[offset] != flake2[flake2_index]) {
            return 0;
        }
    }
    return 1;
}

// Compare flakes by Transversing "RIGHT" and then "LEFT"
int compare_flakes(int flake1[], int flake2[]) {
    int start_pos;
    for (start_pos = 0; start_pos < 6; start_pos++) {
        if (find_right(flake1, flake2, start_pos) || find_left(flake1, flake2, start_pos)) {
            return 1;
        }
    }
    return 0;
}

// As the std sizeOf operation on an array is not supported in C, and must be calculated
// manually, we will use a hard-coded value for now (in order to optimize processing time).
int main(void) {
    int a[6] = {1, 2, 3, 4, 5, 6};
    int b[6] = {3, 2, 1, 6, 5, 4};
    if (compare_flakes(a, b) == 1) {
        printf("The flakes are identical.\n");
    } else {
        printf("The flakes are not identical.\n");
    }
    return 0;
}