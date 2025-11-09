
module load cray/23.12
module load PrgEnv-gnu/8.5.0
make            # builds cpi_omp
make cpi_mpi    # builds cpi_mpi


To format job queue output with specific fields:
squeue -o "%.18i %.8u %.10q %.10a %.20j %.6D %.2t %.20R %.20S %.10L %.10P"


### Exercise 4 — OpenMP thread scaling and compiler optimizations

**1. Varying thread count**
- 1 thread: sequential run, runtime 4.437s, correct π.
- 10 threads: parallel run, runtime 0.4502s, correct π.
- Observation: Parallelism reduces runtime significantly; results remain accurate.

**2. Disabling compiler optimizations (-O0)**
- 128 threads with -O0: runtime 21.41s, π slightly less accurate.
- Observation: Using all threads works, but runtime increases dramatically compared to -O3.
- Compiler optimizations have a huge impact on parallel performance and numerical accuracy.


