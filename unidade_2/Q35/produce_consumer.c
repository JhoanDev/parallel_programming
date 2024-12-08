#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int threads_count = atol(argv[1]);
    if (threads_count > 8)
    {
        printf("insira menos threads!\n");
        exit(1);
    }
    if (threads_count <= 1)
    {
        printf("insira pelo menos 2 threads!\n");
        exit(1);
    }

    Queue *fila = queue_cria();
    int done = !(threads_count & 1) ? (threads_count / 2) : (threads_count / 2 + 1);
    int tokens_lidos = 0;
#pragma omp parallel num_threads(threads_count) default(none) shared(fila, done, threads_count) reduction(+ : tokens_lidos)
    {
        int my_rank = omp_get_thread_num();
        if (!(my_rank & 1))
        {
            char file_name[30];
            snprintf(file_name, sizeof(file_name), "./data/thread_%d.txt", my_rank);
            FILE *my_arq = fopen(file_name, "rt");
            char *linha = (char *)malloc(100 * sizeof(char));
            while (fgets(linha, 100, my_arq) != NULL)
            {
#pragma omp critical
                queue_insere(fila, linha);
                linha = (char *)malloc(100 * sizeof(char));
            }
#pragma omp critical
            done--;
        }
        else
        {
            while (done != 0 || !queue_vazia(fila))
            {
                char *linha = NULL;
                if (!queue_vazia(fila))
                {
                    char *token, *save_ptr = NULL;
#pragma omp critical
                    linha = queue_retira(fila);
                    if (linha != NULL)
                    {
                        token = strtok_r(linha, " \n", &save_ptr);
                        while (token != NULL)
                        {
                            printf("thread %d tokenized -> %s\n", my_rank, token);
                            tokens_lidos++;
                            token = strtok_r(NULL, " \n", &save_ptr);
                        }
                        free(linha);
                    }
                }
            }
        }
    }
    printf("Quantidade de tokens lidos: %d\n", tokens_lidos);
    queue_libera(fila);
    return 0;
}