#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_TERMS 1000000000LL

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int size, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    long long total_terms = N_TERMS;
    long long terms_per_proc = total_terms / size;
    long long start_index;

    double local_pi_sum = 0.0;
    double global_pi_sum = 0.0;

    start_index = (long long)my_rank * terms_per_proc;
    
    for (long long i = 0; i < terms_per_proc; i++) {
        long long current_index = start_index + i;
        
        double denominator = (double)(2 * current_index + 1);
        
        if (current_index % 2 == 0) {
            local_pi_sum += 1.0 / denominator;
        } else {
            local_pi_sum -= 1.0 / denominator;
        }
    }
    
    MPI_Reduce(&local_pi_sum, &global_pi_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        double pi_approx = 4.0 * global_pi_sum;
        
        printf("Leibniz series terms: %lld\n", total_terms);
        printf("Calculated Pi: %.15f\n", pi_approx);
        printf("Actual Pi:     %.15f\n", M_PI);
        printf("Error:         %.15e\n", fabs(pi_approx - M_PI));
    }

    MPI_Finalize();
    
    return 0;
}


