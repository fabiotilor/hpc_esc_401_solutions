#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (size <= 1) {
        if (my_rank == 0) {
            printf("MPI ring requires more than 1 process. Exiting.\n");
        }
        MPI_Finalize();
        return EXIT_SUCCESS;
    }

    MPI_Comm comm_cart;
    int ndims = 1;
    int dims[1] = {size};
    int periods[1] = {1};
    int reorder = 1;

    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &comm_cart);

    MPI_Comm_rank(comm_cart, &my_rank);

    int my_sum = 0;
    int send_rank = my_rank;
    int recv_rank = 0;

    int source, dest;
    
    MPI_Cart_shift(comm_cart, 0, 1, &source, &dest);
    
    int right_rank = dest;
    int left_rank = source;
    
    MPI_Request request[2];
    MPI_Status status[2];

    for (int i = 0; i < size; i++) {
        
        MPI_Irecv(&recv_rank, 1, MPI_INT, left_rank, 0, comm_cart, &request[0]);

        MPI_Isend(&send_rank, 1, MPI_INT, right_rank, 0, comm_cart, &request[1]);
        
        MPI_Waitall(2, request, status);
        
        my_sum += recv_rank;
        send_rank = recv_rank;
    }

    printf("I'm process %d out of %d and the sum is %d.\n", my_rank, size, my_sum);

    MPI_Comm_free(&comm_cart);
    MPI_Finalize();
    
    return EXIT_SUCCESS;
}












































