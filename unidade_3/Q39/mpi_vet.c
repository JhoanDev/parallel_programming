#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void read_n(int *n, int *local_n, int my_rank, int comm_sz, MPI_Comm comm);
void read_scalar(double *scalar, int my_rank, MPI_Comm comm);
void allocate_vectors(double **local_vector1, double **local_vector2, int local_n);
void read_vector(double **local_vet, int local_n, int n, int my_rank, MPI_Comm comm);
void scalar_vector(double **local_vet, int local_n, double scalar);
void inner_prod(double *local_vector1, double *local_vector2, double *prod, int local_n, int my_rank, MPI_Comm comm);
void print_vector(double *local_vector, int n, int local_n, int my_rank, MPI_Comm comm);

int main(void)
{
    double *local_vector1, *local_vector2;
    double prod = 0.0, scalar;
    int n, local_n, my_rank, comm_sz;
    MPI_Comm comm;

    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    read_n(&n, &local_n, my_rank, comm_sz, comm);
    read_scalar(&scalar, my_rank, comm);
    allocate_vectors(&local_vector1, &local_vector2, local_n);
    read_vector(&local_vector1, local_n, n, my_rank, comm);
    read_vector(&local_vector2, local_n, n, my_rank, comm);

    if (my_rank == 0)
        printf("Vetor 1 antes do escalar: ");
    print_vector(local_vector1, n, local_n, my_rank, comm);

    scalar_vector(&local_vector1, local_n, scalar);

    if (my_rank == 0)
        printf("vetor 1 depois do escalar: ");
    print_vector(local_vector1, n, local_n, my_rank, comm);

    if (my_rank == 0)
        printf("\nVetores do produto interno.\n");
    print_vector(local_vector1, n, local_n, my_rank, comm);
    print_vector(local_vector2, n, local_n, my_rank, comm);

    inner_prod(local_vector1, local_vector2, &prod, local_n, my_rank, comm);

    MPI_Finalize();

    return 0;
}

void read_n(int *n, int *local_n, int my_rank, int comm_sz, MPI_Comm comm)
{
    if (my_rank == 0)
    {
        printf("insira o tamanho do vetor: \n");
        scanf("%d", n);
    }
    MPI_Bcast(n, 1, MPI_INT, 0, comm);
    *local_n = *n / comm_sz;
}

void read_scalar(double *scalar, int my_rank, MPI_Comm comm)
{
    if (my_rank == 0)
    {
        printf("Insira o escalar: \n");
        scanf("%lf", scalar);
    }
    MPI_Bcast(scalar, 1, MPI_DOUBLE, 0, comm);
}

void allocate_vectors(double **local_vector1, double **local_vector2, int local_n)
{
    *local_vector1 = (double *)malloc(sizeof(double) * local_n);
    *local_vector2 = (double *)malloc(sizeof(double) * local_n);
}

void read_vector(double **local_vector, int local_n, int n, int my_rank, MPI_Comm comm)
{
    double *aux = NULL;
    if (my_rank == 0)
    {
        aux = (double *)malloc(sizeof(double) * n);
        printf("Insira os elementos do vetor: \n");
        for (int i = 0; i < n; i++)
        {
            scanf("%lf", &aux[i]);
        }
        MPI_Scatter(aux, local_n, MPI_DOUBLE, *local_vector, local_n, MPI_DOUBLE, 0, comm);
        free(aux);
    }
    else
    {
        MPI_Scatter(aux, local_n, MPI_DOUBLE, *local_vector, local_n, MPI_DOUBLE, 0, comm);
    }
}

void scalar_vector(double **local_vet, int local_n, double scalar)
{
    for (int i = 0; i < local_n; i++)
    {
        (*local_vet)[i] *= scalar;
    }
}

void inner_prod(double *local_vector1, double *local_vector2, double *prod, int local_n, int my_rank, MPI_Comm comm)
{
    double local_prod = 0.0;

    for (int i = 0; i < local_n; i++)
    {
        local_prod += local_vector1[i] * local_vector2[i];
    }

    MPI_Reduce(&local_prod, prod, 1, MPI_DOUBLE, MPI_SUM, 0, comm);

    if (my_rank == 0)
    {
        printf("Produto interno total: %.2lf\n", *prod);
    }
}

void print_vector(double *local_vector, int n, int local_n, int my_rank, MPI_Comm comm)
{
    double *aux = NULL;
    if (my_rank == 0)
    {
        aux = malloc(n * sizeof(double));
        MPI_Gather(local_vector, local_n, MPI_DOUBLE, aux, local_n, MPI_DOUBLE, 0, comm);
        for (int i = 0; i < n; i++)
        {
            printf("%.2lf ", aux[i]);
        }
        printf("\n");
        free(aux);
    }
    else
    {
        MPI_Gather(local_vector, local_n, MPI_DOUBLE, aux, local_n, MPI_DOUBLE, 0, comm);
    }
}