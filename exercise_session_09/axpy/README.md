**Exercise 1**

memcopy and daxpy test of size 16777216
-------
timings
-------
axpy (openmp): 0.0628688 s
axpy (openacc): 3.4019 s

============ PASSED

We can see that the GPU-version is about 54 times slower than the CPU-version, this is due to the memory-transfer overhead.


**Exercise 2**

-   **What is the problem with the naive approach?** The problem is that it uses fine-grained **data regions** inside the `nsteps`loop, forcing the 8MB data to be repeatedly copied between the Host (CPU) and Device (GPU) over **1,000 times** (twice per step), resulting in massive memory transfer overhead.

    -   **What is the difference with the naive implementation?** The optimized `_nocopies` version uses a single, coarse-grained `#pragma acc data` region outside the loop, keeping all arrays permanently on the GPU and managing the ping-pong operation with device-side pointer manipulation, thereby eliminating all host-device copies inside the main loop.

    -   **What is the difference in execution time?** Both GPU implementations, even the optimized `_nocopies` one (3.43s), are significantly slower than the OpenMP host version (0.55s), showing that the blur operation is severely **bandwidth-bound**and parallelism cannot overcome the high memory traffic inherent to the stencil calculation.


**Exercise 3**

The dot product calculation is prone to race conditions because numerous parallel threads attempt to simultaneously read and update the single, shared accumulation variable, `sum`. This issue is resolved using the **`reduction`** keyword in the OpenACC directive, specifically: `#pragma acc parallel loop reduction(+:sum)`. Regarding performance, the GPU code performed poorly, taking 3.39s compared to the OpenMP host version's execution time of 0.075s. This significant slowdown (approximately 45×) is typical for highly memory-bound operations like the dot product, where the time spent transferring the 256MB of data between the Host and Device overshadows the time saved by parallel computation.
