#include <stdio.h>

#define COLS 14 
#define ROWS 6

int ii (int x, int y) {
    return (y * COLS) + x;
}

int main() {
    int x, y;

    printf("2D Index (x, y) -> 1D Array Index\n");
    printf("--------------------------------\n");


    for (x = 0; x < COLS; ++x) {
        for (y = 0; y < ROWS; ++y) {
            printf("(%2d,%d) -> %2d\n", x, y, ii(x, y));
        }
    }
    
    printf("\n--- Verification of Calculated Indices ---\n");
    printf("(0, 10) is not possible as x max is 13 and y max is 5. Assuming (10, 0)\n");
    printf("Location (10, 0): %d (Expected: 10)\n", ii(10, 0)); // A[10]
    printf("Location (0, 3): %d (Expected: 42)\n", ii(0, 3)); // A[42] (3 * 14 + 0)
    printf("Location (7, 4): %d (Expected: 63)\n", ii(7, 4)); // A[63] (4 * 14 + 7)

    return 0;
}

