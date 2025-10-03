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

