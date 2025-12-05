#include "jacobi.h"
#include <math.h>
#include <stdio.h>
#include <mpi.h>

extern int ALLREDUCE(double* loc_diff, double* loc_sumdiff);
extern int halo_comm(params p, int my_rank, int size, double** u, double* fromLeft, double* fromRight);

/**
 * @brief       Compute the norm of the difference between two matrices using MPI_Allreduce.
 *
 * @param[in]   p     Parameters
 * @param       mat1  The matrix 1 (u_new)
 * @param       mat2  The matrix 2 (u_old)
 *
 * @return      Returns \sqrt{\sum(mat1_{ij} - mat2_{ij})^2/(nx*ny)}
 */
double norm_diff(params p, double** mat1, double** mat2){
    // Task 3: Compute errors over the entire grid using MPI_Allreduce.

    double local_ret = 0.0;
    double global_ret = 0.0;
    double diff = 0.0;

    int local_nx = p.xmax - p.xmin;
    int local_ny = p.ymax - p.ymin;

    // 1. Calculate local sum of squared differences
    for (int i = 0; i < local_nx; i++){
        for (int j = 0; j < local_ny; j++){
            diff = mat1[i][j] - mat2[i][j];
            local_ret += diff * diff;
        }
    }

    // 2. Use ALLREDUCE (which wraps MPI_Allreduce) to sum up local_ret across all processes.
    // Every process gets the total global sum in global_ret.
    ALLREDUCE(&local_ret, &global_ret);
    
    // 3. Compute the final root-mean-square norm
    global_ret = sqrt(global_ret / ((double)p.nx * p.ny));
    
    return global_ret;
}

/**
 * @brief       Compute a Jacobi iteration to solve Poisson equation with parallel halo exchange.
 * * @param[in]   p     Parameters
 * @param       u_new The new solution
 * @param       u_old The old solution
 * @param       f     The source term
 */
void jacobi_step(params p, double** u_new, double** u_old, double** f, int my_rank, int size){
    double dx = 1.0/((double)p.nx - 1);
    double dy = 1.0/((double)p.ny - 1);
    double dxdy = dx*dy;
    
    int local_nx = p.xmax - p.xmin;
    int local_ny = p.ymax - p.ymin;

    double* fromLeft = new double[local_ny];
    double* fromRight = new double[local_ny];

    // 1. Copy u_new to u_old (u_old is used for RHS of the Jacobi update)
    for (int i=0; i<local_nx; i++){
        for (int j=0; j<local_ny; j++){
            u_old[i][j] = u_new[i][j];
        }
    }

    // 2. Perform halo communication on the old solution data
    halo_comm(p, my_rank, size, u_old, fromLeft, fromRight);
    
    // Determine if the process is on a global boundary (in the x direction)
    bool global_is_left_boundary = (p.xmin == 0);
    bool global_is_right_boundary = (p.xmax == p.nx);


    // --- 3. Compute inner domain update (points that don't depend on received halo data) ---
    int inner_start_i = 1;
    int inner_end_i = local_nx - 1; 

    for (int i = inner_start_i; i < inner_end_i; i++) {
        // Skip global Y boundaries (j=0 and j=local_ny-1)
        for (int j = 1; j < local_ny - 1; j++) {
            u_new[i][j] = 0.25 * (u_old[i-1][j] + u_old[i+1][j] + u_old[i][j-1] + u_old[i][j+1] - dxdy * f[i][j]);
        }
    }


    // --- 4. Compute local boundary updates (the seams using halo data) ---

    // A. Left Seam (local index i = 0)
    if (!global_is_left_boundary) {
        int i = 0; // Local index for the left seam
        // Skip global Y boundaries (j=0 and j=local_ny-1)
        for (int j = 1; j < local_ny - 1; j++) {
            // u_old[i-1][j] is replaced by the halo data: fromLeft[j]
            u_new[i][j] = 0.25 * (fromLeft[j] + u_old[i+1][j] + u_old[i][j-1] + u_old[i][j+1] - dxdy * f[i][j]);
        }
    }

    // B. Right Seam (local index i = local_nx - 1)
    if (!global_is_right_boundary) {
        int i = local_nx - 1; // Local index for the right seam
        // Skip global Y boundaries (j=0 and j=local_ny-1)
        for (int j = 1; j < local_ny - 1; j++) {
            // u_old[i+1][j] is replaced by the halo data: fromRight[j]
            u_new[i][j] = 0.25 * (u_old[i-1][j] + fromRight[j] + u_old[i][j-1] + u_old[i][j+1] - dxdy * f[i][j]);
        }
    }
    
    // 5. Free temporary memory
    delete[] fromLeft;
    delete[] fromRight;
}
