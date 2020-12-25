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

    const int ROOT_ID = 0;
    char initial_array[3] = {'a', 'b', 'c'};

    // If it's the processor with rank 0, modify the array
    if (rank == ROOT_ID)
    {
        for (int i = 0; i < 3; i++)
        {
            initial_array[i] = initial_array[i] + 1;
        }
    }

    // Broadcast send by processor 0
    MPI_Bcast(&initial_array, sizeof(initial_array), MPI_CHAR, ROOT_ID, MPI_COMM_WORLD);

    // Broadcast received by others and printed
    cout << "[" << rank << "] - After broadcast: " << initial_array << endl;

    MPI_Finalize();
    return 0;
}