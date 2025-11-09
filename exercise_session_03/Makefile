
CC = mpicc
CFLAGS = -O2

all: cpi_serial cpi_mpi

getTime.o: getTime.c getTime.h
	$(CC) $(CFLAGS) -c getTime.c

cpi_serial: cpi.c getTime.o
	$(CC) $(CFLAGS) -o cpi_serial cpi.c getTime.o

cpi_mpi: cpi_mpi.c getTime.o
	$(CC) $(CFLAGS) -o cpi_mpi cpi_mpi.c getTime.o

clean:
	rm -f *.o cpi_serial cpi_mpi

