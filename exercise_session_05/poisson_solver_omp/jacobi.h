#ifndef JACOBI_H
#define JACOBI_H

#include "init.h"

#ifdef __cplusplus
extern "C" {
#endif

double norm_diff(params p, double** mat1, double** mat2);
void jacobi_step(params p, double** u_new, double** u_old, double** f);

#ifdef __cplusplus
}
#endif

#endif

