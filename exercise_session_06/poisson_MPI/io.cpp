#include "io.h"
#include "init.h"
#include <fstream>
#include <iostream>
#include <string>
#include <mpi.h>

/**
 * @brief       Output the source term of the Poisson equation in a csv file (local domain).
 *
 * @param[in]   p         Parameters
 * @param       f         Matrix containing the source term
 */
void output_source(params p, double** f, int rank){
    // This is the original skeleton function, keeping it to write local source terms.
    std::string srank = std::to_string(rank);
    std::string file_name = "output/output_source_"+ srank +".csv";
    std::ofstream ofs(file_name, std::ofstream::out | std::ofstream::trunc);
    
    int local_nx = p.xmax - p.xmin;
    int local_ny = p.ymax - p.ymin;
    
    for (int i=0; i<local_nx; i++){
        for (int j=0; j<local_ny; j++){
            ofs << f[i][j];
            if (j != local_ny - 1)
                ofs <<',';
        }
        ofs << '\n';
    }
    std::cout<<"Rank "<<rank<<" is writing output_source to local file.\n";
    ofs.close();
}


/**
 * @brief       Output the approximate solution (Bonus: Rank 0 gathers all data and writes one file)
 *
 * @param[in]   p         Parameters
 * @param[in]   step      The current number of Jacobi steps performed
 * @param       u_new     Matrix containing the approximate solution
 */
void output(params p, int step, double** u_new, int rank){
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_nx = p.xmax - p.xmin;
    int local_ny = p.ymax - p.ymin;
    int local_size = local_nx * local_ny; // Size of local matrix buffer

    double* send_buf = u_new[0];

    int* recvcounts = NULL; // Number of elements to receive from each process
    int* displs = NULL;     // Displacement (offset) for where to place data from each process
    double* recv_buf = NULL; // The final buffer that holds the entire global grid

    if (rank == 0) {
        recvcounts = new int[size];
        displs = new int[size];
        
        int global_size = p.nx * p.ny;
        recv_buf = new double[global_size];

        int current_disp = 0;
        for (int r = 0; r < size; ++r) {
            int r_xmin, r_xmax, r_ymin, r_ymax;
            
            int base = p.nx / size;
            int rem = p.nx % size;
            r_xmin = r * base + (r < rem ? r : rem);
            r_xmax = r_xmin + base + (r < rem ? 1 : 0);
            r_ymin = 0;
            r_ymax = p.ny;
            
            int r_local_nx = r_xmax - r_xmin;
            
            recvcounts[r] = r_local_nx * r_ymax;

            displs[r] = r_xmin * p.ny;
            
        }
    }
    MPI_Gatherv(send_buf, local_size, MPI_DOUBLE, recv_buf, recvcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::string fnum = std::to_string(step);
        fnum.insert(fnum.begin(), 7 - fnum.length(), '0');
        std::string file_name = "output/global_output_" + fnum + ".csv";
        std::ofstream ofs(file_name, std::ofstream::out | std::ofstream::trunc);
        
        for (int i = 0; i < p.nx; i++) {
            for (int j = 0; j < p.ny; j++) {
                ofs << recv_buf[i * p.ny + j];
                if (j != p.ny - 1)
                    ofs << ',';
            }
            ofs << '\n';
        }
        ofs.close();
        std::cout << "Rank 0 wrote global output to " << file_name << "\n";

        delete[] recvcounts;
        delete[] displs;
        delete[] recv_buf;
    }
}
