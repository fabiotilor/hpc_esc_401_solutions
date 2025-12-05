.PHONY: all clean

# Explicitly set the desired compiler. PGI is often recommended for OpenACC.
# You can override these via the command line (e.g., make PGI=0 NVIDIA=1)
NVIDIA ?= 0
CRAY ?= 0
PGI ?= 1
GCC ?= 0
VERBOSE ?= 0
override CPPFLAGS += -I../common

ifeq ($(PE_ENV), NVIDIA) # <-- Fixed: Removed extra ')'
	CXX = nvc++
	CXXFLAGS = -O3 -acc -mp -Minfo=acc -std=c++11 -gpu=cc90
endif

ifeq ($(PE_ENV), CRAY)
	CXX = CC
	CXXFLAGS = -hstd=c++11 -O3 -homp -hacc -dynamic
	ifeq ($(VERBOSE), 1)
		CXXFLAGS += -hmsgs
	endif
endif

ifeq ($(PE_ENV), PGI)
	CXX = pgc++
	CXXFLAGS = -DPGI -std=c++11 -O3 -acc -Minfo=accel -ta=tesla:cc60,pinned 
	LDFLAGS += -L$(CRAY_CUDATOOLKIT_DIR)/lib64 -lcudart
endif

ifeq ($(PE_ENV), GNU)
	# not tested
	CXX = g++
	CXXFLAGS = -std=c++11 -O3 -fopenmp -fopenacc -I$(CRAY_CUDATOOLKIT_DIR)/include
	LDFLAGS += -L$(CRAY_CUDATOOLKIT_DIR)/lib64 -lcudart
endif

OPENACC_BENCHMARKS= axpy.openacc

BENCHMARKS=$(OPENACC_BENCHMARKS)

all: $(BENCHMARKS)

util.o: ../common/util.f03
	$(FC) $(CPPFLAGS) -c $(FCFLAGS) $<

# Using the file name reported in your output: axpy_openacc.cpp
axpy.openacc: axpy_openacc.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(BENCHMARKS) *.cub *.ptx *.o
