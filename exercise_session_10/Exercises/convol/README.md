**Exercise 4**

--- GPU Block Size Tuning ---
| Block Size | Time (sec) |
| :---: | :---: |
| 32 | 0.000190 |
| 64 | 0.000020 |
| 128 | 0.000014 |
| **256** | **0.000012** |
| **512** | **0.000012** |
| 1024 | 0.000013 |
Optimal Block Size: **256** (Time: **0.000012 sec**)
-----------------------------
Convolution took **0.013993 sec.** on GPU before Block Size Tuning
Convolution took **0.004906 sec.** on CPU

The GPU is slower because the problem size is extremely small, so the kernel launch overhead and memory-transfer costs dominate the computation time. The CPU finishes quickly due to its low overhead, while the GPU cannot fully utilize its parallel hardware on such a tiny workload.
