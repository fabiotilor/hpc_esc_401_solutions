#include "init.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_variables(struct params p, double **f, double **u_old, double **u_new)
{
    int i, j;
    double dx = 1.0 / (p.nx - 1);
    double dy = 1.0 / (p.ny - 1);
    double x, y;

    for (i = 0; i < p.nx; i++) {
        x = i * dx;
        for (j = 0; j < p.ny; j++) {
            y = j * dy;

            if (p.rhs_function == 1) {
                f[i][j] = 8 * M_PI * M_PI * sin(2 * M_PI * x) * sin(2 * M_PI * y);
                u_old[i][j] = 0.0;
            } else if (p.rhs_function == 2) {
                f[i][j] = 0.0;
                if (j == 0 && x > 0.25 && x < 0.75)
                    u_old[i][j] = 1.0;
                else
                    u_old[i][j] = 0.0;
            }

            u_new[i][j] = u_old[i][j];
        }
    }
}

void readParameters(const char* filename, struct params* p)
{
    // Default values
    p->nx = 100;
    p->ny = 100;
    p->rhs_function = 1;
    p->foutput = 1000;
    p->nstep_max = 10000;
    p->tol = 1e-6;

    FILE* fp = fopen(filename, "r");
    if (fp) {
        fscanf(fp, "%d %d %d %d %d %lf",
               &p->nx, &p->ny, &p->rhs_function,
               &p->foutput, &p->nstep_max, &p->tol);
        fclose(fp);
    }
}

double** allocateGrid(int nx, int ny, double** M)
{
    M = (double**)malloc(nx * sizeof(double*));
    for (int i = 0; i < nx; i++)
        M[i] = (double*)malloc(ny * sizeof(double));
    return M;
}


