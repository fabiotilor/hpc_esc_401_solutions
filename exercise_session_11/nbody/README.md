**Exercise 1**

Compiling this time, we can see that the perftools created some files as well for analysis.





#################################################################
#                                                               #
#            CrayPat-lite Performance Statistics                #
#                                                               #
#################################################################

CrayPat/X:  Version 23.12.0 Revision 67ffc52e7 sles15.4_x86_64  11/13/23 21:04:20
Experiment:                  lite  lite-samples
Number of PEs (MPI ranks):      1
Numbers of PEs per Node:        1
Numbers of Threads per PE:      1
Number of Cores per Socket:    64
Execution start time:  Fri Nov 28 11:02:41 2025
System name and speed:  nid001897  2.254 GHz (nominal)
AMD   Rome                 CPU  Family: 23  Model: 49  Stepping:  0
Core Performance Boost:  1 PE has CPB capability


Avg Process Time: 12.62 secs         
High Memory:       53.8 MiBytes 53.8 MiBytes per PE

Notes for table 1:

  This table shows functions that have significant exclusive sample
    hits, averaged across ranks.
  For further explanation, use:  pat_report -v -O samp_profile ...

Table 1:  Sample Profile by Function

  Samp% |    Samp | Group
        |         |  Function=[MAX10]
       
 100.0% | 1,257.0 | Total
|------------------------------------
| 100.0% | 1,257.0 | USER
||-----------------------------------
|| 100.0% | 1,257.0 | main
|====================================

Notes for table 2:

  This table shows functions, and line numbers within functions, that
    have significant exclusive sample hits, averaged across ranks.
  For further explanation, use:  pat_report -v -O samp_profile+src ...

Table 2:  Sample Profile by Group, Function, and Line

  Samp% |    Samp | Group
        |         |  Function=[MAX10]
        |         |   Source
        |         |    Line
       
 100.0% | 1,257.0 | Total
|----------------------------------------------------------------------------
| 100.0% | 1,257.0 | USER
||---------------------------------------------------------------------------
|| 100.0% | 1,257.0 | main
|||--------------------------------------------------------------------------
3||  83.5% | 1,049.0 | hpc_esc_401_solutions/exercise_session_11/nbody/nbody.cpp
||||-------------------------------------------------------------------------
4|||   3.1% |    39.0 | line.38
4|||  23.2% |   292.0 | line.39
4|||  57.1% |   718.0 | line.40
||||=========================================================================
3||  16.5% |   208.0 | c++/12/bits/stl_vector.h
4||        |         |  line.386
|============================================================================

Observation:  MPI utilization

    No suggestions were made because each node has only one rank.


Notes for table 3:

  This table shows memory traffic for numa nodes, taking for each numa
    node the maximum value across nodes. It also shows the balance in
    memory traffic by showing the top 3 and bottom 3 node values.
  For further explanation, use:  pat_report -v -O mem_bw ...

Table 3:  Memory Bandwidth by Numanode

  Memory |    Read |   Write |    Thread |  Memory |  Memory | Numanode
 Traffic |  Memory |  Memory |      Time | Traffic | Traffic | 
  GBytes | Traffic | Traffic |           |  GBytes |       / | 
         |  GBytes |  GBytes |           |   / Sec | Nominal | 
         |         |         |           |         |    Peak | 
|------------------------------------------------------------------------
|    0.01 |    0.01 |    0.00 | 12.597305 |    0.00 |    0.0% | numanode.7
|========================================================================

Notes for table 4:

  This table shows energy and power usage for the nodes with the
    maximum, mean, and minimum usage, as well as the sum of usage over
    all nodes.
    Energy and power for accelerators is also shown, if available.
  For further explanation, use:  pat_report -v -O program_energy ...

Table 4:  Program Energy and Power Usage from Cray PM

Total

  
===========================================================
  Total
-----------------------------------------------------------
  PM Energy Node    236 W     2,977 J
  PM Energy Cpu      51 W       642 J
  PM Energy Memory  119 W     1,496 J
  Process Time            12.619565 secs
===========================================================

Program invocation:  nbody

For a complete report with expanded tables and notes, run:
  pat_report /users/fdimeo/hpc_esc_401_solutions/exercise_session_11/nbody/nbody+94437-853243717s

For help identifying callers of particular functions:
  pat_report -O callers+src /users/fdimeo/hpc_esc_401_solutions/exercise_session_11/nbody/nbody+94437-853243717s
To see the entire call tree:
  pat_report -O calltree+src /users/fdimeo/hpc_esc_401_solutions/exercise_session_11/nbody/nbody+94437-853243717s

For interactive, graphical performance analysis, run:
  app2 /users/fdimeo/hpc_esc_401_solutions/exercise_session_11/nbody/nbody+94437-853243717s

================  End of CrayPat-lite output  ==========================



The parts of the code that took the most CPU time are lines **39** and **40** within the `main` function of `nbody.cpp`, accounting for **23.2%** and **57.1%** of the total exclusive samples, respectively. This is likely due to these lines containing the **core computational loop** of the n-body simulation, where the forces between particles are calculated and integrated over time.









**Exercise 2**


Time with **sqrt():**

real	0m12.835s
user	0m12.828s
sys	0m0.004s


Time with **sqrtf():**

real	0m7.420s
user	0m7.404s
sys	0m0.012s





**Exercise 3**


After vectorising flag:

/usr/include/c++/12/bits/vector.tcc:515:30: optimized: basic block part vectorized using 32 byte vectors
/usr/include/c++/12/bits/random.tcc:412:42: optimized: loop vectorized using 32 byte vectors
/usr/include/c++/12/bits/random.tcc:404:32: optimized: loop vectorized using 32 byte vectors
/usr/include/c++/12/bits/random.tcc:404:32: optimized: loop vectorized using 16 byte vectors
/usr/include/c++/12/bits/vector.tcc:96:27: optimized: basic block part vectorized using 32 byte vectors


Vectorisation report after adjustments:

/usr/include/c++/12/bits/vector.tcc:699:31: optimized: basic block part vectorized using 32 byte vectors
/usr/include/c++/12/bits/stl_algobase.h:921:22: optimized: loop vectorized using 32 byte vectors
/usr/include/c++/12/bits/stl_algobase.h:921:22: optimized: loop vectorized using 16 byte vectors
/usr/include/c++/12/bits/stl_algobase.h:921:22: optimized: loop vectorized using 32 byte vectors
/usr/include/c++/12/bits/stl_algobase.h:921:22: optimized: loop vectorized using 16 byte vectors
/usr/include/c++/12/bits/stl_algobase.h:921:22: optimized: loop vectorized using 32 byte vectors
/usr/include/c++/12/bits/stl_algobase.h:921:22: optimized: loop vectorized using 16 byte vectors
/usr/include/c++/12/bits/stl_algobase.h:921:22: optimized: loop vectorized using 32 byte vectors
/usr/include/c++/12/bits/stl_algobase.h:921:22: optimized: loop vectorized using 16 byte vectors
/usr/include/c++/12/bits/vector.tcc:617:31: optimized: basic block part vectorized using 32 byte vectors
/usr/include/c++/12/bits/random.tcc:412:42: optimized: loop vectorized using 32 byte vectors
/usr/include/c++/12/bits/random.tcc:404:32: optimized: loop vectorized using 32 byte vectors
/usr/include/c++/12/bits/random.tcc:404:32: optimized: loop vectorized using 16 byte vectors
/usr/include/c++/12/bits/stl_vector.h:100:4: optimized: basic block part vectorized using 32 byte vectors
/usr/include/c++/12/bits/stl_vector.h:100:4: optimized: basic block part vectorized using 32 byte vectors

Time:

real	0m7.047s
user	0m7.035s
sys	0m0.001s


It runs faster but not much faster, I would say it behaved as expected.

