#include <cuda.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Define the matrix size */
#define NX 200
#define NY 100

/* Size of a block */
#define BLOCKSIZE 256

__global__ void kernadd(float* mout, float* min1, float* min2, int nx, int ny)
{
    int i, j, index;
    index = blockDim.x * blockIdx.x + threadIdx.x;

    /* Boundary checking */
    j = index / nx;
    i = index - j * nx;

    if ((i < nx) && (j < ny))
        mout[index] = min1[index] + min2[index];
}

__global__ void kernadd_2d(float* mout, float* min1, float* min2, int nx, int ny)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < nx && y < ny) {
        int index = y * nx + x;
        mout[index] = min1[index] + min2[index];
    }
}

/*******************************************************/
/*  We initialize the vectors with random values       */
/*******************************************************/

void Init(float* mat, int nx, int ny) {
    int i, j;
    for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++) {
            mat[i + j * nx] = drand48();
        }
    }
}

/*******************************************************/
/*                     MAIN PROGRAM                    */
/*******************************************************/

int main() {
    int i = 0, error = 0, nx = NX, ny = NY;
    float diff;
    int total_elements = nx * ny;

    /* Matrix allocation on Host */
    float *mat_in1 = (float*) malloc(total_elements * sizeof(float));
    float *mat_in2 = (float*) malloc(total_elements * sizeof(float));
    float *mat_out = (float*) malloc(total_elements * sizeof(float));

    /* Matrix allocation on Device */
    float *mat_out_gpu, *mat_in1_gpu, *mat_in2_gpu;
    cudaMalloc((void**)&mat_in1_gpu, total_elements * sizeof(float));
    cudaMalloc((void**)&mat_in2_gpu, total_elements * sizeof(float));
    cudaMalloc((void**)&mat_out_gpu, total_elements * sizeof(float));

    /* Matrix initialization */
    Init(mat_in1, nx, ny);
    Init(mat_in2, nx, ny);

    /* Copy to device */
    cudaMemcpy(mat_in1_gpu, mat_in1, total_elements * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(mat_in2_gpu, mat_in2, total_elements * sizeof(float), cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks(
        (nx + threadsPerBlock.x - 1) / threadsPerBlock.x,
        (ny + threadsPerBlock.y - 1) / threadsPerBlock.y
    );

    kernadd_2d<<<numBlocks, threadsPerBlock>>>(mat_out_gpu, mat_in1_gpu, mat_in2_gpu, nx, ny);

    int numBlocks_1D = (total_elements + BLOCKSIZE - 1) / BLOCKSIZE;
    kernadd<<<numBlocks_1D, BLOCKSIZE>>>(mat_out_gpu, mat_in1_gpu, mat_in2_gpu, nx, ny);

    cudaDeviceSynchronize();

    /* Copy back to host */
    cudaMemcpy(mat_out, mat_out_gpu, total_elements * sizeof(float), cudaMemcpyDeviceToHost);

    /* Free device memory */
    cudaFree(mat_out_gpu);
    cudaFree(mat_in1_gpu);
    cudaFree(mat_in2_gpu);

    /* Check correctness */
    for (i = 0; i < total_elements; i++) {
        diff = mat_out[i] - (mat_in1[i] + mat_in2[i]);
        if (fabs(diff) > 1e-7f) {
            error = 1;
            break;
        }
    }

    if (error)
        printf("FAILED\n");
    else
        printf("PASSED\n");

    free(mat_in1);
    free(mat_in2);
    free(mat_out);

    return 0;
}

