Exercise 1: MPI Ring Communication Deadlock
===========================================

- What happens when you run the code? Why?
------------------------------------------

### Observation

When running the `ring.c` program with two or more processes (e.g., `mpirun -np 4 ./ring`), the program immediately **stops or hangs indefinitely** before printing any final output. The program never reaches `MPI_Finalize()`, indicating a **deadlock**.

### Explanation (Why the Deadlock Occurs)

The deadlock is a direct result of using the **Synchronous Send (`MPI_Ssend`)** communication mode in a circular dependency:

1.  **Synchronous Requirement:** `MPI_Ssend` is a blocking call that *will not return* until the matching receive (`MPI_Recv`) is posted by the receiving process **AND** the message transfer has been completed (i.e., the data has left the sender's buffer, often requiring the receiver to be ready).

2.  **Circular Dependency:** In the loop, every single process executes the following sequence:

    -   `MPI_Ssend` (to its right neighbor)

    -   `MPI_Recv` (from its left neighbor)

-   Process 0 tries to send to Process 1 and waits for Process 1 to call `MPI_Recv`.

-   Process 1 tries to send to Process 2 and waits for Process 2 to call `MPI_Recv`.

-   ...

-   Process N-1 tries to send to Process 0 and waits for Process 0 to call `MPI_Recv`.

Since every process is stuck on its `MPI_Ssend` call, waiting for its neighbor to enter the `MPI_Recv` state, **no process can proceed** to the receive part of the code. This creates a circular waiting condition where no action can be completed, resulting in the program hanging (a collective deadlock).


Exercise 2: Deadlock Resolution via Asymmetric Communication
============================================================

The program now runs successfully because the even/odd rank asymmetry guarantees that every synchronous send finds a corresponding receive, thereby breaking the deadlock's circular waiting pattern. However, this is not optimal as it imposes sequential communication phases, making the dedicated, single-call `MPI_Sendrecv` a more efficient solution.


Exercise 3: Deadlock Resolution via Non-Blocking Communication

The non-blocking methods (MPI_Irecv + MPI_Isend + MPI_Waitall) are superior to the synchronous (MPI_Ssend + parity check) solution because they eliminate the need for complex symmetry-breaking logic. By posting both the send and receive requests simultaneously before blocking, they allow the MPI runtime to manage the communication dependencies efficiently, potentially overlapping computation and communication and guaranteeing freedom from deadlock.

Exercise 3: Deadlock Resolution via Non-Blocking Communication
==============================================================

The non-blocking methods (`MPI_Irecv` + `MPI_Isend` + `MPI_Waitall`) are superior to the synchronous (`MPI_Ssend` + parity check) solution because they **eliminate the need for complex symmetry-breaking logic**. By posting both the send and receive requests simultaneously before blocking, they allow the MPI runtime to manage the communication dependencies efficiently, potentially overlapping computation and communication and guaranteeing freedom from deadlock.




Exercise 4: Cartesian Topology Communicator
===========================================

What advantage does the new communicator provide?
-------------------------------------------------

The primary advantage of using the **Cartesian Topology Communicator (`MPI_Cart_create`)** and **`MPI_Cart_shift`** is **programmer convenience and code portability**. It allows the programmer to quickly set up complex, periodic communication patterns (like rings or multi-dimensional grids) without manually calculating neighbor ranks, index arithmetic, or implementing custom logic for wrapping boundary conditions. This makes the code cleaner, less error-prone, and easier to scale to higher dimensions.


Exercise 2: $\pi$ Approximation using the Leibniz Series (MPI)
==================================================

This analysis details the implementation of the $\pi$ approximation using the Leibniz infinite series, $\frac{\pi}{4} = \sum_{k=0}^{\infty} \frac{(-1)^k}{2k + 1}$, using parallel computation with MPI.
