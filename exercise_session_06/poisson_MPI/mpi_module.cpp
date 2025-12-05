// Method: 1D decomposition along x (each rank gets a contiguous block of x indices).
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"


// finalize MPI
int start_MPI(int *my_rank, int *size) {
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, size);
    return 0;
}


int close_MPI(){
    MPI_Finalize();
    return 0;
}

int mpi_get_domain(int nx, int ny, int my_rank, int size, int* min_x, int* max_x, int* min_y, int* max_y){
    int base = nx / size;
    int rem  = nx % size;

    int xmin_local = my_rank * base + (my_rank < rem ? my_rank : rem);
    int local_width = base + (my_rank < rem ? 1 : 0);
    int xmax_local = xmin_local + local_width; // exclusive upper bound: [xmin_local, xmax_local)

    int ymin_local = 0;
    int ymax_local = ny;

    *min_x = xmin_local;
    *max_x = xmax_local;
    *min_y = ymin_local;
    *max_y = ymax_local;

    printf("rank %d: domain x=[%d,%d) y=[%d,%d) (local nx=%d, ny=%d)\n",
           my_rank, *min_x, *max_x, *min_y, *max_y, (*max_x - *min_x), (*max_y - *min_y));

    return 0;
}

//Exercise 2: Method III
int halo_comm(params p, int my_rank, int size, double** u,
              double* fromLeft, double* fromRight) {

    int local_nx = p.xmax - p.xmin;
    int local_ny = p.ymax - p.ymin;

    int left  = (my_rank > 0) ? my_rank - 1 : MPI_PROC_NULL;
    int right = (my_rank < size - 1) ? my_rank + 1 : MPI_PROC_NULL;

    MPI_Request reqs[4];

    // 1. Prepare the columns to send
    double* sendLeft  = new double[local_ny];
    double* sendRight = new double[local_ny];
    for (int j = 0; j < local_ny; j++) {
        sendLeft[j]  = u[0][j];                 // leftmost column
        sendRight[j] = u[local_nx - 1][j];      // rightmost column
    }

    // 2. Post non-blocking receives first
    MPI_Irecv(fromLeft,  local_ny, MPI_DOUBLE, left,  0, MPI_COMM_WORLD, &reqs[0]);
    MPI_Irecv(fromRight, local_ny, MPI_DOUBLE, right, 1, MPI_COMM_WORLD, &reqs[1]);

    // 3. Post non-blocking sends
    MPI_Isend(sendLeft,  local_ny, MPI_DOUBLE, left,  1, MPI_COMM_WORLD, &reqs[2]);
    MPI_Isend(sendRight, local_ny, MPI_DOUBLE, right, 0, MPI_COMM_WORLD, &reqs[3]);

    // 4. (Optional) Do computation on *inner* domain here
    // For example, you could call `jacobi_inner(p, u_old, u_new)` or similar

    // 5. Wait for all communications to finish before updating boundary
    MPI_Waitall(4, reqs, MPI_STATUSES_IGNORE);

    delete[] sendLeft;
    delete[] sendRight;

    printf("Rank %d completed halo exchange with L=%d, R=%d\n", my_rank, left, right);
    return 0;
}





int ALLREDUCE(double* loc_diff, double* loc_sumdiff){
    MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    return 0;
}

