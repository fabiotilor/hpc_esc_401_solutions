#include "jacobi.h"
#include <omp.h>

void jacobi_step(params p, double** u_new, double** u_old, double** f) {
    int i, j;
    double dx2 = 1.0 / ((p.nx-1)*(p.nx-1));
    double dy2 = 1.0 / ((p.ny-1)*(p.ny-1));
    double denom = 2*(dx2 + dy2);

    #pragma omp parallel for collapse(2)
    for (i = 1; i < p.nx-1; i++) {
        for (j = 1; j < p.ny-1; j++) {
            u_new[i][j] = ((u_old[i-1][j] + u_old[i+1][j])*dy2 +
                           (u_old[i][j-1] + u_old[i][j+1])*dx2 -
                           f[i][j]) / denom;
        }
    }

    // swap u_new and u_old
    #pragma omp parallel for collapse(2)
    for (i = 0; i < p.nx; i++) {
        for (j = 0; j < p.ny; j++) {
            u_old[i][j] = u_new[i][j];
        }
    }
}

