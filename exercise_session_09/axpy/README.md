**Exercise 1**

memcopy and daxpy test of size 16777216
-------
timings
-------
axpy (openmp): 0.0628688 s
axpy (openacc): 3.4019 s

============ PASSED

We can see that the GPU-version is about 54 times slower than the CPU-version, this is due to the memory-transfer overhead.

