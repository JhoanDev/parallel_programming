#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int n = atol(argv[1]);
    int threads_count = atol(argv[2]);
    int a[n];
    int b[n];
    b[0] = 0;
    for (int i = 1; i < n; i++)
        b[i] = b[i - 1] + i;
    printf("Resultado serial ->");
    for (int i = 0; i < n; i++)
        printf(" %d", b[i]);

#pragma omp parallel for num_threads(threads_count) default(none) shared(n, a)
    for (int i = 1; i < n; i++)
        a[i] = (i * (i + 1) / 2);

    printf("\nResultado paralelo ->");
    for (int i = 0; i < n; i++)
        printf(" %d", a[i]);
    printf("\n");

    return 0;
}
