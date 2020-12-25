#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the world size, i.e. the numbers of processors
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the current processor's rank which is executing the code
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double local_mpi_bcast_time = 0.0;
    MPI_Barrier(MPI_COMM_WORLD);
    double startTime = MPI_Wtime();

    double localTime = MPI_Wtime() - startTime;

    printf("[%d]\tWaited\t%.20f (time units)\n", rank, localTime);

    MPI_Finalize();
    return 0;
}