#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int threads_count = atol(argv[1]);
    unsigned long long int lancamentos, acertos = 0;
    printf("insira a quantidade de lancamentos: ");
    scanf("%llu", &lancamentos);
    unsigned int seed = time(NULL), thread_seed;
    double x, y, distance, pi_estimate;

#pragma omp parallel num_threads(threads_count) default(none) \
private(thread_seed, x, y, distance) shared(seed, lancamentos) reduction(+ : acertos)
    {
        thread_seed = seed + omp_get_thread_num();
#pragma omp for
        for (int i = 0; i < lancamentos; i++)
        {
            x = ((double)rand_r(&thread_seed) / RAND_MAX) * 2.0 - 1.0;
            y = ((double)rand_r(&thread_seed) / RAND_MAX) * 2.0 - 1.0;
            distance = x * x + y * y;
            if (distance <= 1)
                acertos++;
        }
    }
    pi_estimate = 4.0 * ((double)acertos / lancamentos);
    printf("pi = %lf\n", pi_estimate);
    return 0;
}