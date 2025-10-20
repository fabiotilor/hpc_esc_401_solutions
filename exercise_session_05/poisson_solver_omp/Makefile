# Compiler
CC = icpx

# Flags for C and C++ files
CFLAGS   = -O3 -ffast-math -mavx2 -qopenmp
CPPFLAGS = -O3 -ffast-math -mavx2 -qopenmp

# Source files
C_SRCS   = init.c jacobi.c norm_diff.c
CPP_SRCS = main.cpp io.cpp

# Object files
C_OBJS   = $(C_SRCS:.c=.o)
CPP_OBJS = $(CPP_SRCS:.cpp=.o)
OBJS     = $(C_OBJS) $(CPP_OBJS)

# Default target
all: poisson_solver_omp

# Linking the executable
poisson_solver_omp: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ files
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f *.o poisson_solver

