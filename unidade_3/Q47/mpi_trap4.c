/* File:     mpi_trap4.c
 * Purpose:  Use MPI to implement a parallel version of the trapezoidal
 *           rule.  This version uses collective communications and
 *           MPI derived datatypes to distribute the input data and
 *           compute the global sum.
 *
 * Input:    The endpoints of the interval of integration and the number
 *           of trapezoids
 * Output:   Estimate of the integral from a to b of f(x)
 *           using the trapezoidal rule and n trapezoids.
 *
 * Compile:  mpicc -g -Wall -o mpi_trap4 mpi_trap4.c
 * Run:      mpiexec -n <number of processes> ./mpi_trap4
 *
 * Algorithm:
 *    1.  Each process calculates "its" interval of
 *        integration.
 *    2.  Each process estimates the integral of f(x)
 *        over its interval using the trapezoidal rule.
 *    3a. Each process != 0 sends its integral to 0.
 *    3b. Process 0 sums the calculations received from
 *        the individual processes and prints the result.
 *
 * Note:  f(x) is all hardwired.
 *
 * IPP:   Section 3.5 (pp. 117 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

/* Build a derived datatype for distributing the input data */
void Build_mpi_type(double *a_p, double *b_p, long long *n_p,
                    MPI_Datatype *input_mpi_t_p);

/* Calculate local integral  */
double Trap(double left_endpt, double right_endpt, long long trap_count,
            double base_len);

/* Function we're integrating */
double f(double x);

int main(int agrc, char *argv[])
{
   int my_rank, comm_sz;
   long long n, local_n;
   double a, b, h, local_a, local_b;
   double local_int, total_int;
   a = atoll(argv[1]);
   b = atoll(argv[2]);
   n = atoll(argv[3]);

   MPI_Init(NULL, NULL);
   double local_start, local_finish, local_elapsed, elapsed;
   MPI_Barrier(MPI_COMM_WORLD);
   local_start = MPI_Wtime();

   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   h = (b - a) / n;
   local_n = n / comm_sz;
   local_a = a + my_rank * local_n * h;
   local_b = local_a + local_n * h;

   local_int = Trap(local_a, local_b, local_n, h);
   MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

   local_finish = MPI_Wtime();
   local_elapsed = local_finish - local_start;
   MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
   if (my_rank == 0)
   {
      printf("Tempo decorrido = %.6lf\n", elapsed);
   }
   MPI_Finalize();

   return 0;
} /*  main  */

/*------------------------------------------------------------------
 * Function:     Build_mpi_type
 * Purpose:      Build a derived datatype so that the three
 *               input values can be sent in a single message.
 * Input args:   a_p:  pointer to left endpoint
 *               b_p:  pointer to right endpoint
 *               n_p:  pointer to number of trapezoids
 * Output args:  input_mpi_t_p:  the new MPI datatype
 */
void Build_mpi_type(
    double *a_p /* in  */,
    double *b_p /* in  */,
    long long *n_p /* in  */,
    MPI_Datatype *input_mpi_t_p /* out */)
{

   int array_of_blocklengths[3] = {1, 1, 1};
   MPI_Datatype array_of_types[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_LONG_LONG};
   MPI_Aint a_addr, b_addr, n_addr;
   MPI_Aint array_of_displacements[3] = {0};

   MPI_Get_address(a_p, &a_addr);
   MPI_Get_address(b_p, &b_addr);
   MPI_Get_address(n_p, &n_addr);
   array_of_displacements[1] = b_addr - a_addr;
   array_of_displacements[2] = n_addr - a_addr;
   MPI_Type_create_struct(3, array_of_blocklengths,
                          array_of_displacements, array_of_types,
                          input_mpi_t_p);
   MPI_Type_commit(input_mpi_t_p);
} /* Build_mpi_type */

/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Serial function for estimating a definite integral
 *               using the trapezoidal rule
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
double Trap(
    double left_endpt /* in */,
    double right_endpt /* in */,
    long long trap_count /* in */,
    double base_len /* in */)
{
   double estimate, x;
   long long i;

   estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
   for (i = 1; i <= trap_count - 1; i++)
   {
      x = left_endpt + i * base_len;
      estimate += f(x);
   }
   estimate = estimate * base_len;

   return estimate;
} /*  Trap  */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x /* in */)
{
   return x * x;
} /* f */
