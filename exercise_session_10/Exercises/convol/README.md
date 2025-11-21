**Exercise 4**

--- GPU Block Size Tuning ---
Block size   32 took 0.000190 sec.
Block size   64 took 0.000020 sec.
Block size  128 took 0.000014 sec.
Block size  256 took 0.000012 sec.
Block size  512 took 0.000012 sec.
Block size 1024 took 0.000013 sec.
Optimal Block Size: 256 (Time: 0.000012 sec)
-----------------------------
Convolution took 0.000012 sec. on GPU
Convolution took  0.004949 sec. on CPU
PASSED

The GPU is slower because the problem size is extremely small, so the kernel launch overhead and memory-transfer costs dominate the computation time. The CPU finishes quickly due to its low overhead, while the GPU cannot fully utilize its parallel hardware on such a tiny workload.

