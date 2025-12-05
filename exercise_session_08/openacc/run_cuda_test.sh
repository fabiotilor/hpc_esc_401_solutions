#!/bin/bash

UENV_ENV="prgenv-nvfortran/25.7:v2@daint%gh200 --view=nvfort"

# $1 is NUM_BLOCK, $2 is NUM_THREAD

# 1. Initial compilation of base code
if [ ! -f my_pi_cuda_runner ]; then
    echo "Attempting initial compilation of base code..."
    uenv run $UENV_ENV -- nvcc -O3 -arch=sm_90 cpi_cuda.cu gettime.c -o my_pi_cuda_runner
fi

# 2. Modify the source file
cp cpi_cuda.cu cpi_cuda_temp.cu
sed -i "s/#define NUM_BLOCK.*/#define NUM_BLOCK $1/" cpi_cuda_temp.cu
sed -i "s/#define NUM_THREAD.*/#define NUM_THREAD $2/" cpi_cuda_temp.cu

# 3. Recompile the new configuration
echo "Compiling for B=$1, T=$2"
uenv run $UENV_ENV -- nvcc -O3 -arch=sm_90 cpi_cuda_temp.cu gettime.c -o my_pi_cuda_$1_$2

# 4. Execute the code and extract the time
# Execution must also happen inside the UENV environment to link against the correct libraries.
OUTPUT=$(uenv run $UENV_ENV -- srun ./my_pi_cuda_$1_$2 2>/dev/null | head -n 1)

# 5. Extract the time value (e.g., 0.04891)
TIME=$(echo $OUTPUT | awk '{print $NF}')

# 6. Print the result
echo "$1,$2,$TIME" >> scaling_results.csv

# 7. Clean up
rm -f my_pi_cuda_$1_$2 cpi_cuda_temp.cu
