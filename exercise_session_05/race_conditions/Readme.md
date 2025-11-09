Wrap only the shared update inside critical or atomic, not the whole loop — or replace with reduction to avoid serialization entirely.



gcc serial.c -o serial_prog
[eiger][fdimeo@eiger-ln002 race_conditions]$ ./serial_prog
Size of integer array/file: 1000000
max number in file: 38747
number of 0s in file: 646016
true number of 0s in file: 646016
[eiger][fdimeo@eiger-ln002 race_conditions]$ gcc -fopenmp parallel.c -o omp_prog
[eiger][fdimeo@eiger-ln002 race_conditions]$ export OMP_NUM_THREADS=4
[eiger][fdimeo@eiger-ln002 race_conditions]$ ./omp_prog
Size of integer array/file: 1000000
max number in file: 38747
number of 0s in file: 646016
true number of 0s in file: 646016

