#include <mpi.h>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the world size, i.e. the numbers of processors
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the current processor's rank which is executing the code
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    printf("Processor with rank %d from %d processors\n", world_rank, world_size);

    MPI_Finalize();
}