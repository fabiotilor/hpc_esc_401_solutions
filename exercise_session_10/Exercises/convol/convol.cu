#include <time.h>
#include <cuda.h>
#include <stdio.h>
#define STOP 0
#define START 1

extern "C" void chrono(int kind, float *time);

__global__ void kconvol(float *gpu_a, float *gpu_b, int n) {
    int i, j, l;

    /* Global thread index */
    l = blockDim.x * blockIdx.x + threadIdx.x;

    /* Compute (i, j) from linear index */
    j = l / n;
    i = l - j * n;

    if ((i >= n) || (j >= n)) return;

    if ((i == 0) || (j == 0) || (i == n - 1) || (j == n - 1)) {
        gpu_b[l] = gpu_a[l]; /* edges are untouched */
    }
    else {
        gpu_b[l] = (1.0f / 5.0f) *
                   (gpu_a[l - n] + gpu_a[l - 1] + gpu_a[l] +
                    gpu_a[l + 1] + gpu_a[l + n]);
    }
}

extern "C" void gpu_convol(float *a, float *b, int n) {
    float *gpu_a;
    float *gpu_b;
    cudaError_t err;
    float time_gpu;
    size_t size = n * n * sizeof(float);

    /* Variables for tuning */
    int best_block_size = 0;
    float best_time = 9999.0f;

    if (n * n < 1024) {
        printf("Note: Matrix size N=%d is too small for meaningful tuning.\n", n);
    }

    err = cudaMalloc(&gpu_a, size);
    if (err != 0) {
        printf("Error allocating gpu_a: %s\n", cudaGetErrorString(err));
        exit(1);
    }

    err = cudaMalloc(&gpu_b, size);
    if (err != 0) {
        printf("Error allocating gpu_b: %s\n", cudaGetErrorString(err));
        exit(1);
    }

    cudaMemcpy(gpu_a, a, size, cudaMemcpyHostToDevice);

    printf("\n--- GPU Block Size Tuning ---\n");
    int total_elements = n * n;

    for (int block_size = 32; block_size <= 1024; block_size *= 2) {
        int numBlocks = (total_elements + block_size - 1) / block_size;
        float current_time;

        chrono(START, &current_time);
        kconvol<<<numBlocks, block_size>>>(gpu_a, gpu_b, n);
        err = cudaDeviceSynchronize();
        chrono(STOP, &current_time);

        if (err != 0) {
            printf("Error during synchronization for block size %d: %s\n",
                   block_size, cudaGetErrorString(err));
            exit(1);
        }

        printf("Block size %4d took %f sec.\n", block_size, current_time);

        if (current_time < best_time) {
            best_time = current_time;
            best_block_size = block_size;
        }
    }

    printf("Optimal Block Size: %d (Time: %f sec)\n", best_block_size, best_time);
    printf("-----------------------------\n");

    /* Final run using optimal block size */
    int final_num_blocks = (total_elements + best_block_size - 1) / best_block_size;

    chrono(START, &time_gpu);
    kconvol<<<final_num_blocks, best_block_size>>>(gpu_a, gpu_b, n);
    err = cudaDeviceSynchronize();
    chrono(STOP, &time_gpu);

    printf("Convolution took %f sec. on GPU\n", time_gpu);

    cudaMemcpy(b, gpu_b, size, cudaMemcpyDeviceToHost);
    if (err != 0) {
        printf("%s\n", cudaGetErrorString(err));
        exit(1);
    }

    cudaFree(gpu_a);
    cudaFree(gpu_b);
}

