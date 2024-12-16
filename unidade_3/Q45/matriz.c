#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void read_matriz(int **matriz, int *n, int my_rank, MPI_Comm comm);
void create_triangular_type(int n, MPI_Datatype old, MPI_Datatype *new_datatype);
void print_tringular_sup(int n, int **matriz, int my_rank);

int main(void)
{
    int comm_sz, my_rank, *matriz, n;
    MPI_Comm comm;

    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    read_matriz(&matriz, &n, my_rank, comm);
    MPI_Datatype upper_triangular;
    create_triangular_type(n, MPI_INT, &upper_triangular);
    if (my_rank == 0)
        MPI_Send(matriz, 1, upper_triangular, 1, 0, comm);
    if (my_rank == 1)
        MPI_Recv(matriz, 1, upper_triangular, 0, 0, comm, NULL);
    print_tringular_sup(n, &matriz, my_rank);

    free(matriz);
    free(upper_triangular);
    MPI_Type_free(&upper_triangular);
    MPI_Finalize();
    return 0;
}

void read_matriz(int **matriz, int *n, int my_rank, MPI_Comm comm)
{
    if (my_rank == 0)
    {
        int i, j;
        printf("Insira a ordem da matriz: ");
        fflush(stdout);
        scanf("%d", n);
        *matriz = (int *)malloc((*n) * (*n) * sizeof(int));
        for (i = 0; i < (*n); i++)
        {
            for (j = 0; j < (*n); j++)
            {
                printf("insira o elemento [%d][%d] da matriz: ", i, j);
                fflush(stdout);
                scanf("%d", &(*matriz)[i * (*n) + j]);
            }
        }
        printf("\n----- Matriz lida -----\n");
        fflush(stdout);
        for (i = 0; i < (*n); i++)
        {
            for (j = 0; j < (*n); j++)
            {
                printf("%3d ", (*matriz)[i * (*n) + j]);
                fflush(stdout);
            }
            printf("\n");
            fflush(stdout);
        }
    }

    MPI_Bcast(n, 1, MPI_INT, 0, comm);
    if (my_rank == 1)
    {
        *matriz = (int *)malloc((*n) * (*n) * sizeof(int));
    }
}

void create_triangular_type(int n, MPI_Datatype old, MPI_Datatype *new_datatype)
{
    int i;
    int qnt[n];
    int desl[n];
    for (i = 0; i < n; i++)
    {
        qnt[i] = n - i;
        desl[i] = i * n + i;
    }
    MPI_Type_indexed(n, qnt, desl, old, new_datatype);
    MPI_Type_commit(new_datatype);
}

void print_tringular_sup(int n, int **matriz, int my_rank)
{
    if (my_rank == 1)
    {
        int i, j;
        printf("\n----- Triangular superior -----\n");
        fflush(stdout);
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (j < i)
                {
                    printf("   ");
                    fflush(stdout);
                }
                else
                {
                    printf("%3d", (*matriz)[i * n + j]);
                    fflush(stdout);
                }
            }
            printf("\n");
            fflush(stdout);
        }
    }
}
