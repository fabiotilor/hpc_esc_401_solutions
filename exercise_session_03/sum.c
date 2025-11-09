#include "getTime.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
    float r2;
} coord;

int main(int argc, char *argv[]) {
    const int N = 1024*1024*256;
    coord *data;
    int i;
    double sum;
    
    data = malloc(N * sizeof(coord));
    assert(data);
    double start = getTime();
    sum = 0.0;
    #pragma omp parallel for reduction(+ : sum)

    for(i=0; i<N; ++i) {
        data[i].x = i & 31;
        data[i].y = i & 63;
        data[i].z = i & 15;
        data[i].r2 = data[i].x*data[i].x + data[i].y*data[i].y + data[i].z*data[i].z;
        sum += sqrt(data[i].r2);
    }
    double end = getTime();
    printf("Sum = %f\n", sum);
    printf("Execution time: %f s\n", end - start);
    return 0;
}
