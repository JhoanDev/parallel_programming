#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define TAM_VET 25000
#define NUM_EXECUCOES 10

void copy_array(int *source, int *destination, int size);
void print_array(int arr[], int n);
void generate_random_array(int *arr, int size);
int is_sorted(int arr[], int n);

void count_sort_parallel(int a[], int n, int threads_count);
void count_sort(int a[], int n);

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[])
{
    int threads_count = atol(argv[1]);
    int vet[TAM_VET];
    int vet2[TAM_VET];
    int vet3[TAM_VET];
    srand(time(NULL));
    double start, finish, elapsed_time;
    double media_paralelo = 0.0;
    double media_serial = 0.0;
    double media_qsort = 0.0;

    for (int exec = 0; exec < NUM_EXECUCOES; exec++)
    {
        generate_random_array(vet, TAM_VET);
        copy_array(vet, vet2, TAM_VET);
        copy_array(vet, vet3, TAM_VET);

        start = omp_get_wtime();
        count_sort_parallel(vet, TAM_VET, threads_count);
        finish = omp_get_wtime();
        elapsed_time = finish - start;
        media_paralelo += elapsed_time;

        if (!is_sorted(vet, TAM_VET))
            return 1;

        start = omp_get_wtime();
        count_sort(vet2, TAM_VET);
        finish = omp_get_wtime();
        elapsed_time = finish - start;
        media_serial += elapsed_time;

        if (!is_sorted(vet2, TAM_VET))
            return 1;

        start = omp_get_wtime();
        qsort(vet3, TAM_VET, sizeof(int), compare);
        finish = omp_get_wtime();
        elapsed_time = finish - start;
        media_qsort += elapsed_time;

        if (!is_sorted(vet3, TAM_VET))
            return 1;
    }
    media_paralelo /= NUM_EXECUCOES;
    media_serial /= NUM_EXECUCOES;
    media_qsort /= NUM_EXECUCOES;

    printf("Tempo médio de execução de count_sort_parallel: %.6f segundos\n", media_paralelo);
    printf("Tempo médio de execução de count_sort serial: %.6f segundos\n", media_serial);
    printf("Tempo médio de execução de qsort serial: %.6f segundos\n", media_qsort);

    return 0;
}
int is_sorted(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

void count_sort_parallel(int a[], int n, int threads_count)
{
    int i, j, count;
    int *temp = malloc(n * sizeof(int));
#pragma omp parallel num_threads(threads_count) default(none) \
private(i, j, count) shared(a, n, temp)
    {
#pragma omp for
        for (i = 0; i < n; i++)
        {
            count = 0;
            for (j = 0; j < n; j++)
            {
                if (a[j] < a[i]) count++;
                else if (a[j] == a[i] && j < i) count++;
            }
            temp[count] = a[i];
        }
    }
#pragma omp parallel num_threads(threads_count)
    {
        int my_rank = omp_get_thread_num();
        int chunk = n / threads_count;
        int rest = n % threads_count;
        int start, end;
        if (my_rank < rest)
        {
            start = my_rank * (chunk + 1);
            end = start + chunk + 1;
        }
        else
        {
            start = my_rank * chunk + rest;
            end = start + chunk;
        }
        memcpy(&a[start], &temp[start], (end - start) * sizeof(int));
    }
    free(temp);
}

// a[] = 9 8 8 8 3 1 1
// thread 0 = 9 8
// i = 0    count = 6
// i = 1    count = 3
// thread 1 = 8 8
// i = 2    count = 4
// i = 3    count = 5
// thread 2 = 3 1
// i = 4    count = 2
// i = 5    count = 0
// thread 3 = 1
// i = 6    count = 1
// temp[] = 1 1 3 8 8 8 9

void count_sort(int a[], int n)
{
    int i, j, count;
    int *temp = malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        count = 0;
        for (j = 0; j < n; j++)
        {
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        }
        temp[count] = a[i];
    }
    memcpy(a, temp, n * sizeof(int));
    free(temp);
}

void print_array(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void copy_array(int *source, int *destination, int size)
{
    for (int i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }
}

void generate_random_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % TAM_VET + 1;
    }
}