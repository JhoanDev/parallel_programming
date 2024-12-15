#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define COUNT 8

int main(void)
{
    int i, comm_sz, my_rank;
    double *local_vet, *prefix_sum;
    MPI_Comm comm;

    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    srand(time(NULL) + my_rank);

    local_vet = (double *)malloc(sizeof(double) * COUNT);
    prefix_sum = (double *)malloc(sizeof(double) * COUNT);

    for (i = 0; i < COUNT; i++)
    {
        local_vet[i] = rand() % (COUNT * comm_sz);
    }

    MPI_Barrier(comm);
    MPI_Scan(local_vet, prefix_sum, COUNT, MPI_DOUBLE, MPI_SUM, comm);
    MPI_Barrier(comm);

    for (i = 0; i < comm_sz; i++)
    {
        if (my_rank == i)
        {
            printf("Processo %d - Vetor de entrada: ", my_rank);
            for (int j = 0; j < COUNT; j++)
            {
                printf("%.1lf ", local_vet[j]);
            }
            printf("\n");

            printf("Processo %d - Soma de prefixos: ", my_rank);
            for (int j = 0; j < COUNT; j++)
            {
                printf("%.1f ", prefix_sum[j]);
            }
            printf("\n");
        }
        MPI_Barrier(comm);
    }

    free(local_vet);
    free(prefix_sum);

    MPI_Finalize();
    return 0;
}