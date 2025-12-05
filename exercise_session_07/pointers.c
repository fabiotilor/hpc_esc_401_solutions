#include <stdio.h>

int main() {
    int p[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    printf("d. Value of *p: %d\n", *p);

    printf("e. Value of p[0]: %d\n", p[0]);

    printf("f. Value of p[3]: %d\n", p[3]);

    printf("g. Value of *(p+5): %d\n", *(p+5));

    printf("h. Value of *p+5: %d\n", *p+5);

    int *q = p - 1;

    printf("j. Value of q[0] (*(p-1)): %d\n", q[0]);

    printf("k. Value of *(q+10): %d\n", *(q+10));

    printf("l. Value of *(q+11) (*(p+10)): %d\n", *(q+11));

    return 0;
}

