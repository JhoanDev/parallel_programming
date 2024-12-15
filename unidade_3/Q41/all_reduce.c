#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(void)
{
    int i, comm_sz, my_rank, my_val = 0, sum = 0, temp_val, source, dest;
    MPI_Comm comm;

    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    my_val = my_rank + 1;
    sum = temp_val = my_val;
    source = my_rank;
    
    if (my_rank == (comm_sz - 1))
    {
        source = my_rank - 1;
        dest = 0;
    }
    else if (my_rank == 0)
    {
        source = comm_sz - 1;
        dest = 1;
    }
    else
    {
        source = my_rank - 1;
        dest = my_rank + 1;
    }

    for (i = 1; i < comm_sz; i++)
    {
        MPI_Sendrecv_replace(&temp_val, 1, MPI_INT, dest, 0, source, 0, comm, NULL);
        sum += temp_val;
    }

    printf("Processo %d - Soma total: %d\n", my_rank, sum);

    MPI_Finalize();
    return 0;
}
