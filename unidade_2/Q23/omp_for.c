#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int n = atol(argv[1]);
    int threads_count = atol(argv[2]);

#pragma omp parallel num_threads(threads_count) default(none) shared(n)
    {
        int my_rank = omp_get_thread_num();
        char *text_thread = (char *)malloc(500 * sizeof(char));
        int count = 0;
        int execucoes[n];

#pragma omp for
        for (int i = 0; i < n; i++)
            execucoes[count++] = i;

        sprintf(text_thread, "Thread %d: Iteracoes -> %d", my_rank, execucoes[0]);
        for (int i = 1; i < count; i++)
        {
            char execucao[10];
            sprintf(execucao, " -- %d", execucoes[i]);
            strcat(text_thread, execucao); 
        }

        printf("%s\n", text_thread);
        free(text_thread);           
    }
    return 0;
}
