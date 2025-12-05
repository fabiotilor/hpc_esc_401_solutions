#include "jacobi.h"
#include <math.h>

void jacobi_step(params p, double **u_new, double **u_old, double **f)
{
    int i, j;
    double dx = 1.0 / (p.nx - 1);
    double dx2 = dx * dx;

    for (i = 1; i < p.nx - 1; i++) {
        for (j = 1; j < p.ny - 1; j++) {
            u_new[i][j] = 0.25 * (u_old[i-1][j] + u_old[i+1][j]
                                + u_old[i][j-1] + u_old[i][j+1]
                                - dx2 * f[i][j]);
        }
    }
}
