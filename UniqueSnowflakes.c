#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100000

// NOTE: This approach follows a design pattern in which the comparative array is transversed in both directions.
//       Binary Search Trees are an example of a "Tranvserse in Both Directions" design pattern.

// The "comparison only" solution has a big O factor of O(n^2). This is because we are comparing every element to every other element.
// The "comparison only" solution is not efficient enough to pass the time limit.
// We can limit the number of comparisons by creating a "code" for each snowflake, which is the sum of the elements.
// We can then compare the codes to determine if the snowflakes can be illiminated from the comparison.
// This code will become the index of the "code" array. HOWEVER, the size of the "code" array will be too large to hold all possible codes.
// We can limit the size of the "code" array by using the modulus operator to reduce its index.
// In effect we are creating a HASH TABLE.

// Hash Function - This function will return a unique index for each snowflake.
int code(int flake[])
{
    return (flake[0] + flake[1] + flake[2] + flake[3] + flake[4] + flake[5]) % SIZE;
}

// Now we need a linked list to store the repeated codes, otherwise we will have collisions problems.
typedef struct flake_node
{
    int flake[6];
    struct flake_node *next;
} flake_node;

// Transverse "RIGHT" to determine match.
// If match is found, return 1, otherwise return 0. (Boolean)
int find_right(int flake1[], int flake2[], int start)
{
    int offset;
    for (offset = 0; offset < 6; offset++)
    {
        // Using modulus to wrap around the array.
        if (flake1[offset] != flake2[(start + offset) % 6])
        {
            return 0;
        }
    }
    return 1;
}

// Transverse "LEFT" to determine match.
// If match is found, return 1, otherwise return 0. (Boolean)
// Modulus will NOT work here, because we are going backwards.
int find_left(int flake1[], int flake2[], int start)
{
    int offset, flake2_index;
    for (offset = 0; offset < 6; offset++)
    {
        flake2_index = start - offset;
        if (flake2_index < 0)
        {
            flake2_index += 6;
        }
        if (flake1[offset] != flake2[flake2_index])
        {
            return 0;
        }
    }
    return 1;
}

// Compare flakes by Transversing "RIGHT" and then "LEFT"
int compare_flakes(int flake1[], int flake2[])
{
    int start_pos;
    for (start_pos = 0; start_pos < 6; start_pos++)
    {
        if (find_right(flake1, flake2, start_pos) || find_left(flake1, flake2, start_pos))
        {
            return 1;
        }
    }
    return 0;
}

// ** Refactored - Original code listed below. **
void find_identical(flake_node *flakes[])
{
    flake_node *node1, *node2;
    int i;
    for (i = 0; i < SIZE; i++)
    {
        node1 = flakes[i];
        while (node1 != NULL)
        {
            node2 = node1->next;
            while (node2 != NULL)
            {
                if (compare_flakes(node1->flake, node2->flake))
                {
                    printf("Twin snowflakes found.\n");
                    return;
                }
                node2 = node2->next;
            }
            node1 = node1->next;
        }
    }
    printf("No two snowflakes are alike.\n");
}

// ** Refactored - Original code listed below. **
int main(void)
{
    // Changed the array from a 2D array to a 1D array of pointers to nodes.
    // static is used to ensure that the array is allocated its own memory space, due to its size.
    static flake_node *flakes[SIZE] = {NULL};
    flake_node *snow; // snow is a pointer to the flake nodes
    int n, i, j, flake_code;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        snow = malloc(sizeof(flake_node));
        if (snow == NULL)
        {
            fprintf(stderr, "Memory allocation error.\n");
            exit(1);
        }
        for (j = 0; j < 6; j++)
        {
            scanf("%d", &snow->flake[j]);
        }
        flake_code = code(snow->flake);  // Calculate the code for the snowflake
        snow->next = flakes[flake_code]; // Add the snowflake to the linked list

        // Now update the head of the linked list.
        // We are adding it at the beginning because of speed
        // (Not necessary to transverse the list to find a location for adding - saves time.)
        flakes[flake_code] = snow; // Update the head of the linked list
    }
    find_identical(flakes);
    free(snow);
    return 0;
}

// ** Refactored code listed above. **
// Initial function to determine concept of unique snowflakes
// void find_identical(int flakes[][6], int n) {
//     int i, j;
//     for (i = 0; i < n; i++) {

// Start at the next element, otherwise we are comparing the same element
// and will get a false positive.
//         for (j = i + 1; j < n; j++) {
//             if (compare_flakes(flakes[i], flakes[j])) {
//                 printf("Twin snowflakes found.\n");
//                 return;
//             }
//         }
//     }
//     printf("No two snowflakes are alike.\n");

// As the std sizeOf operation on an array is not supported in C, and must be calculated
// manually, we will use a hard-coded value for now (in order to optimize processing time).
// int main(void) {
//     static int flakes[SIZE][6];
//     int n, i, j;
//     scanf("%d", &n);
//     for(i=0; i <n; i++)
//         for (j=0; j<6; j++)
//             scanf("%d", &flakes[i][j]);
//     find_identical(flakes, n);
//     return 0;
// }
