// Using CUDA device to calculate pi
#include <stdio.h>
#include <cuda.h>
#include <stdlib.h> // For EXIT_FAILURE
extern "C" double getTime(void);

#define NBIN 1000000000  // Number of bins

// Array definitions for scaling study
const int BLOCKS[] = {60, 120, 180, 240, 300, 360, 420, 600};
const int THREADS[] = {16, 32, 48, 64, 80, 96, 112, 128, 144, 160};
const int NUM_BLOCKS_TO_TEST = sizeof(BLOCKS) / sizeof(BLOCKS[0]);
const int NUM_THREADS_TO_TEST = sizeof(THREADS) / sizeof(THREADS[0]);

// Kernel that executes on the CUDA device (unchanged)
__global__ void cal_pi(double *sum, int nbin, double step, int nthreads, int nblocks) {
        int i;
        double x;
        int idx = blockIdx.x*blockDim.x+threadIdx.x;  // Sequential thread index across the blocks
        for (i=idx; i< nbin; i+=nthreads*nblocks) {
                x = (i+0.5)*step;
                sum[idx] += 4.0/(1.0+x*x);
        }
}

// Main routine that executes on the host
int main(void) {
    printf("NUM_BLOCK,NUM_THREAD,TIME\n");
    double step = 1.0/NBIN; 

    for (int b_idx = 0; b_idx < NUM_BLOCKS_TO_TEST; b_idx++) {
        int num_blocks = BLOCKS[b_idx];

        for (int t_idx = 0; t_idx < NUM_THREADS_TO_TEST; t_idx++) {
            int num_threads = THREADS[t_idx];

            dim3 dimGrid(num_blocks, 1, 1);
            dim3 dimBlock(num_threads, 1, 1);

            double *sumHost = NULL, *sumDev = NULL;
            double pi = 0;
            int tid;

            // Dynamic memory allocation based on current block/thread count
            size_t size = num_blocks * num_threads * sizeof(double);
            sumHost = (double *)malloc(size);
            cudaMalloc((void **) &sumDev, size);
            
            if (sumHost == NULL || sumDev == NULL) {
                fprintf(stderr, "Allocation failure for B=%d, T=%d. Skipping...\n", num_blocks, num_threads);
                if (sumHost) free(sumHost);
                if (sumDev) cudaFree(sumDev);
                continue;
            }

            // --- Calculation and Timing ---
            double start = getTime();
            
            cudaMemset(sumDev, 0, size);
            cal_pi <<<dimGrid, dimBlock>>> (sumDev, NBIN, step, num_threads, num_blocks);
            cudaDeviceSynchronize(); // Ensure kernel completes before measuring time
            cudaMemcpy(sumHost, sumDev, size, cudaMemcpyDeviceToHost);
            
            // Host reduction
            for(tid = 0; tid < num_blocks * num_threads; tid++)
                pi += sumHost[tid];
            pi *= step;

            double delta = getTime() - start;
            
            // Output in CSV format
            printf("%d,%d,%.16g\n", num_blocks, num_threads, delta);

            // Cleanup
            free(sumHost);
            cudaFree(sumDev);
        }
    }

    return 0;
}
