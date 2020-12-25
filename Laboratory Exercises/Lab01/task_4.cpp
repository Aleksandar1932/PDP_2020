#include <mpi.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int NUMBER_OF_ELEMENTS_IN_ARRAY = 12;

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the world size, i.e. the numbers of processors
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the current processor's rank which is executing the code
    int processor_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_rank);

    // Initialize the array with size dividable by 4

    int array[NUMBER_OF_ELEMENTS_IN_ARRAY] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // Each processor including the 4th one is sending the appropriate 25% of the elemets from the array;

    int start = processor_rank * (NUMBER_OF_ELEMENTS_IN_ARRAY / 4);
    int end = (processor_rank * (NUMBER_OF_ELEMENTS_IN_ARRAY / 4) + (NUMBER_OF_ELEMENTS_IN_ARRAY / 4));
    int send_buffer[NUMBER_OF_ELEMENTS_IN_ARRAY / 4];

    int j = 0;
    for (int i = start; i < end; i++)
    {
        send_buffer[j] = array[i];
        j++;
    }

    MPI_Send(&send_buffer, NUMBER_OF_ELEMENTS_IN_ARRAY / 4, MPI_INT, 3, 0, MPI_COMM_WORLD);

    // The 4th processor is receieveing all of the parts and summing them
    if (processor_rank == (world_size - 1))
    {
        int total_sum = 0;

        for (int rFrom = 0; rFrom <= (world_size - 1); rFrom++)
        {
            int receieve_buffer[NUMBER_OF_ELEMENTS_IN_ARRAY / 4];
            MPI_Recv(&receieve_buffer, (NUMBER_OF_ELEMENTS_IN_ARRAY / 4) + 1, MPI_INT, rFrom, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int i = 0; i < NUMBER_OF_ELEMENTS_IN_ARRAY / 4; i++)
            {
                total_sum += receieve_buffer[i];
            }
        }
        cout << "The total sum is: " << total_sum << endl;
    }

    MPI_Finalize();
}