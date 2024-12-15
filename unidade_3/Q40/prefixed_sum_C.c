#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void read_vector(double *x, int n, int my_rank, MPI_Comm comm);
void print_result(double *x, int n, int my_rank, MPI_Comm comm);

int main(void)
{
    int n, i, comm_sz, my_rank;
    double local_x, aux;
    MPI_Comm comm;

    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    n = comm_sz;
    read_vector(&local_x, n, my_rank, comm);

    for (i = 1; i < comm_sz; i *= 2)
    {
        if (my_rank + i < comm_sz)
        {
            MPI_Send(&local_x, 1, MPI_DOUBLE, my_rank + i, 0, comm);
        }
        if (my_rank >= i)
        {
            MPI_Recv(&aux, 1, MPI_DOUBLE, my_rank - i, 0, comm, NULL);
            local_x += aux;
        }
    }

    print_result(&local_x, n, my_rank, comm);

    MPI_Finalize();
    return 0;
}

void read_vector(double *x, int n, int my_rank, MPI_Comm comm)
{
    double *aux = NULL;
    if (my_rank == 0)
    {
        aux = (double *)malloc(sizeof(double) * n);
        printf("Insira os elementos do vetor: ");
        fflush(stdout);
        for (int i = 0; i < n; i++)
        {
            scanf("%lf", &aux[i]);
        }
        MPI_Scatter(aux, 1, MPI_DOUBLE, x, 1, MPI_DOUBLE, 0, comm);
        free(aux);
    }
    else
    {
        MPI_Scatter(aux, 1, MPI_DOUBLE, x, 1, MPI_DOUBLE, 0, comm);
    }
}

void print_result(double *x, int n, int my_rank, MPI_Comm comm)
{
    double *aux = NULL;
    if (my_rank == 0)
    {
        aux = (double *)malloc(sizeof(double) * n);
        MPI_Gather(x, 1, MPI_DOUBLE, aux, 1, MPI_DOUBLE, 0, comm);
        printf("Vetor resultante das somas parciais: ");
        fflush(stdout);
        for (int i = 0; i < n; i++)
        {
            printf("%.1lf ", aux[i]);
        }
        printf("\n");
        free(aux);
    }
    else
    {
        MPI_Gather(x, 1, MPI_DOUBLE, aux, 1, MPI_DOUBLE, 0, comm);
    }
}
