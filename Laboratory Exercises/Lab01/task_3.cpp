#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the world size, i.e. the numbers of processors
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the current processor's rank which is executing the code
    int processor_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_rank);

    for (int iter = 0; iter <= 10; iter++)
    {

        int BUFFER_SIZE = 128;
        char message[BUFFER_SIZE] = {};

        if (processor_rank == 0)
        {
            if (iter != 0)
            {
                // Receieve message from 2 if iteration != 0;
                MPI_Recv(&message, BUFFER_SIZE, MPI_CHAR, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                cout << "[P1]\t" << message << endl;
            }

            // Send message to 1
            string temp;
            sprintf(message, "Message #%04d", iter);
            MPI_Send(&message, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        }
        else if (processor_rank == 1)
        {
            // Receieve message from 0
            MPI_Recv(&message, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Send message to 2
            MPI_Send(&message, BUFFER_SIZE, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
        }
        else if (processor_rank == 2)
        {
            // Receieve message from 2
            MPI_Recv(&message, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            MPI_Send(&message, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
            // Send message to 1
        }
        else
        {
            cerr << "The maximum number of processors for this task is 3" << endl;
        }
    }

    MPI_Finalize();
}