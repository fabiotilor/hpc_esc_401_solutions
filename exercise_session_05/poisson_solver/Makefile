CC = icpx

CFLAGS = -O3 -ffast-math -mavx2

C_SRCS   = init.c jacobi.c norm_diff.c
CPP_SRCS = main.cpp io.cpp

C_OBJS   = $(C_SRCS:.c=.o)
CPP_OBJS = $(CPP_SRCS:.cpp=.o)
OBJS     = $(C_OBJS) $(CPP_OBJS)

all: poisson_solver

poisson_solver: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o poisson_solver



