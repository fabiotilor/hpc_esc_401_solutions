**Exercise 1**
No, the output does not all have the same run time:

PI = 3.141592653589793 computed in 1.029 seconds
PI = 3.141592653589793 computed in 0.001348 seconds
PI = 3.141592653589793 computed in 0.001342 seconds
PI = 3.141592653589793 computed in 0.001356 seconds
PI = 3.141592653589793 computed in 0.001343 seconds

The first iteration is always slower due to overhead.



**Exercise 2**

The comparison of execution times reveals a significant trade-off between initialization and steady-state speed. The OpenACC code incurs a massive initial overhead, taking 1.029 seconds, which is ≈21× slower than the CUDA code's initial time of 0.04891 seconds. However, the OpenACC's subsequent iterations are extremely fast at ≈0.00135 seconds, indicating that while CUDA has a lower startup cost, both methods achieve excellent, comparable steady-state performance once the kernel is actively running on the H100 GPU



**Exercise 3**

The execution time is strongly inversely proportional to the total number of threads, demonstrating significant scaling as the product of $NUM\_BLOCK$ and $NUM\_THREAD$ increases. This scaling is characterized by a rapid decrease in time that transitions into a performance plateau once the workload is sufficient to fully utilize the GPU. The initial speedup is primarily explained by **latency hiding**, where a high density of threads allows the Streaming Multiprocessors to conceal memory access delays by constantly switching between active tasks. The subsequent plateau occurs because the hardware reaches **resource saturation**, meaning any additional threads only increase scheduling overhead without improving concurrent throughput..
