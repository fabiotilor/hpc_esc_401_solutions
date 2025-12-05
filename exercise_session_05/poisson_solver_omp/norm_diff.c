#include "jacobi.h"
#include <math.h>
#include <omp.h>

double norm_diff(params p, double** mat1, double** mat2) {
    double sum = 0.0;
    int i, j;

    #pragma omp parallel for reduction(+:sum) collapse(2)
    for (i = 0; i < p.nx; i++) {
        for (j = 0; j < p.ny; j++) {
            double diff = mat1[i][j] - mat2[i][j];
            sum += diff * diff;
        }
    }

    return sqrt(sum / (p.nx * p.ny));
}


