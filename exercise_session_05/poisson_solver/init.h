#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <cmath>

struct params {
    int rhs_function;
    int nx;
    int ny;
    int foutput;
    int nstep_max;
    double tol;
};

#ifdef __cplusplus
extern "C" {
#endif

void readParameters(const char*, params*);
double** allocateGrid(int nx, int ny, double** M);
double source_term(double x, double y, int function);
double exact_solution(double x, double y, int function);
double boundary(double x, double y, int function);
void init_f(params p, double **f);
void init_variables(params p, double **f, double **u_old, double **u_new);

#ifdef __cplusplus
}
#endif

#endif

