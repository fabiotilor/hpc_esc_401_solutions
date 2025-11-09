#!/bin/bash -l

#SBATCH --job-name=OpenACC_Pi_GH200
#SBATCH --account=uzh8     # <-- REPLACE with your CSCS project account ID
#SBATCH --time=00:10:00                 
#SBATCH --partition=debug               
#SBATCH --nodes=1                       
#SBATCH --ntasks-per-node=1             
#SBATCH --gpus-per-node=1               
#SBATCH --constraint=gpu              # <-- CORRECTED: Use 'gpu' constraint

# ----------------- UENV Integration via Slurm -----------------
# This loads the environment required for running the executable
#SBATCH --uenv=prgenv-nvfortran/25.7:v2@daint%gh200:/user-environment
#SBATCH --view=nvfort

# ----------------- Execution -----------------
srun ./my_pi_acc
