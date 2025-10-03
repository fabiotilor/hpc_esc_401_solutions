# Exercise Session 03 - HPC ESC 401

## Programs

- **cpi.c** - Serial computation of pi.
- **cpi_mpi.c** - MPI parallel computation of pi using multiple processes.
- **getTime.c / getTime.h** - Timing utility functions.
- **sum.c** - Auxiliary exercise file.

## Compilation

Make sure the HPC environment is loaded:

```bash
module load cray/23.12
module load nvhpc-hpcx-cuda12/24.3
module load hpcx-mt-ompi
make clean
make
```

## Execution

- **Serial run:**

```bash
srun ./cpi_serial
```

- **MPI parallel run (4 processes):**

```bash
srun -n 4 ./cpi_mpi
```

Or using :

```bash
mpirun -n 4 ./cpi_mpi
```

## Observed Execution Times

| Program       | Time (s)       | Notes |
|---------------|----------------|-------|
| Serial        | 0.3802         | Single process computation |
| MPI (compute) | 0.3754         | Only computation + MPI_Reduce |
| MPI (full)    | 0.979447       | Includes MPI_Init() and setup overhead |

## Observations

- MPI parallelization divides the work among multiple processes, giving slightly faster computation.
- Initialization and library setup in MPI introduces extra overhead, which is noticeable for small workloads.
- For larger workloads, MPI would achieve greater speedup.

# Task 2

1. What results does your code produce?
The sequential code with -O0 takes ~4.914 s.
With higher optimization flags:
-O1 → 1.958 s
-O2 → 1.079 s
-O3 → 1.082 s
OpenMP parallelization (#pragma omp parallel for reduction(+ : sum)) with 1–8 threads:
1 thread → 1.108 s
2 threads → 0.565 s
4 threads → 0.282 s
8 threads → 0.157 s
The sum value remains consistent up to minor floating-point differences caused by parallel reduction order.
2. Do you know other ways to get timings?
Yes, besides your getTime() function:
POSIX timing functions: clock_gettime(CLOCK_MONOTONIC, &ts) or gettimeofday().
CPU clocks: clock() in time.h measures CPU time.
Profiling tools: perf, gprof, Intel VTune, or NVIDIA Nsight for more detailed profiling.
MPI timing: MPI_Wtime() for distributed programs.
3. How big is the difference in execution time with the different flags?
-O0 → baseline, no optimizations: ~4.9 s.
-O1 → ~2× faster.
-O2 → ~4.5× faster than -O0.
-O3 → similar to -O2, minimal improvement because the code is memory-bound.
Optimization drastically reduces runtime, especially moving from no optimization (-O0) to -O2.
4. How did the compiler optimize the code?
-O1: Basic optimizations (constant folding, dead code elimination, simple instruction scheduling).
-O2: More aggressive optimizations (loop unrolling, vectorization hints, improved instruction scheduling).
-O3: Includes all -O2 optimizations plus more aggressive vectorization and inlining.
The compiler may also optimize memory access patterns, but the code is memory-bound, so gains plateau at -O2/-O3.
5. How can you make it even faster?
Parallelization: Using OpenMP, as you already did.
Vectorization / SIMD: Use #pragma omp simd or compiler-specific vector intrinsics.
Memory optimization:
Align arrays for cache efficiency.
Reduce memory allocations, reuse arrays if possible.
Blocking / tiling: Improve cache locality in loops.
Fused operations: Combine operations to reduce temporary computations.
Higher core counts: Run on more threads if memory bandwidth allows.

1. Where did you insert the line?
The OpenMP directive was inserted just before the main computational loop that sums over the array:

2. How did you compile?
gcc sum.c getTime.c -o sum_omp -O3 -fopenmp -lm


#include "getTime.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
    float r2;
} coord;

int main(int argc, char *argv[]) {
    const int N = 1024*1024*256;
    coord *data;
    int i;
    double sum;

    data = malloc(N * sizeof(coord));
    assert(data);
    double start = getTime();
    sum = 0.0;

    #pragma omp parallel for reduction(+ : sum)
    for(i = 0; i < N; ++i) {
        data[i].x = i & 31;
        data[i].y = i & 63;
        data[i].z = i & 15;
        data[i].r2 = data[i].x*data[i].x + data[i].y*data[i].y + data[i].z*data[i].z;
        sum += sqrt(data[i].r2);
    }

    double end = getTime();
    printf("Sum = %f\n", sum);
    printf("Execution time: %f s\n", end - start);
    return 0;
}
4. Job script example

#!/bin/bash
#SBATCH --job-name=sum_omp
#SBATCH --output=sum_omp.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:10:00
#SBATCH --partition=standard

module load gcc
export OMP_NUM_THREADS=4

srun ./sum_omp

