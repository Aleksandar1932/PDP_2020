#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define BR_ELEMENTI 100

double najdi_avg(double *niza, int br_elem)
{
    int sum = 0;
    float prosek = 0;
    for (int i = 1; i < br_elem; i++)
    {
        sum += niza[i];
    }
    return (sum * 1.0) / (br_elem * 1.0);
}

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    int i = 0;
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    double elementi_za_sortiranje[BR_ELEMENTI];
    double elem_po_proces = BR_ELEMENTI / world_size;

    if (world_rank == 0)
    {
        for (i = 0; i < BR_ELEMENTI; i++)
        {
            elementi_za_sortiranje[i] = i;
        }
    }

    double *niza_po_proces = (double *)malloc(sizeof(double) * elem_po_proces);

    MPI_Scatter(elementi_za_sortiranje, elem_po_proces, MPI_DOUBLE, niza_po_proces, elem_po_proces, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double avg = najdi_avg(niza_po_proces, elem_po_proces);

    printf("[%d]: Lokalen prosek:\t %.2f\n", world_rank, avg);
    double *lokalni_avg = NULL;

    if (world_rank == 0)
    {
        lokalni_avg = (double *)malloc(sizeof(double) * world_size);
    }
    MPI_Gather(&avg, 1, MPI_DOUBLE, lokalni_avg, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if (world_rank == 0)
    {
        printf("Globalen prosek:\t%.2f\n", najdi_avg(lokalni_avg, world_size));
    }
}
