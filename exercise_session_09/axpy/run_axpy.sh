#!/bin/bash
#SBATCH --job-name=axpy_acc
#SBATCH --account=uzh8          
#SBATCH --constraint=gpu          
#SBATCH --time=00:05:00          
#SBATCH --nodes=1                 
#SBATCH --ntasks-per-node=1      

ulimit -s unlimited

module load nvhpc


srun -n 1 ./axpy.openacc 24
