#!/bin/bash
#SBATCH --job-name=blur_acc
#SBATCH --account=uzh8           # IMPORTANT: Use the specified account for GPU jobs
#SBATCH --constraint=gpu          # Request a GPU node
#SBATCH --time=00:05:00           # Time limit
#SBATCH --nodes=1                 # Number of nodes
#SBATCH --ntasks-per-node=1       # One CPU core per node for launching the task

ulimit -s unlimited

module load nvhpc

srun -n 1 ./blur.openacc 20 500
