#!/bin/bash -l

#SBATCH --job-name=CUDA_Scaling_Study
#SBATCH --account=uzh8                 # REPLACE with your project ID
#SBATCH --time=00:30:00                
#SBATCH --partition=debug              
#SBATCH --nodes=1                      
#SBATCH --ntasks-per-node=1            
#SBATCH --gpus-per-node=1              
#SBATCH --constraint=gpu               

# Load the environment required for execution
#SBATCH --uenv=prgenv-nvfortran/25.7:v2@daint%gh200:/user-environment
#SBATCH --view=nvfort

# Execute the single compiled program
srun ./my_pi_cuda_scaling
