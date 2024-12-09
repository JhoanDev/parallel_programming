#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

#define MAX_LINE 100

void get_text(char *lines[], int *qnt_line);
void free_memory(char *lines[], int *qnt_line);
char *strtok_r_mod(const char *text, const char *delim, char **last_tok);

int main(int agrc, char *argv[])
{
    int thread_count = atol(argv[1]);
    char **lines = (char **)malloc(sizeof(char *) * (MAX_LINE / 2));
    int line_count = 0;
    get_text(lines, &line_count);

    int i, j, my_rank = 0;
    char *my_token = NULL;
    char *my_line = NULL;

#pragma omp parallel num_threads(thread_count) default(none) private(my_rank, i, j, my_token, my_line) shared(lines, line_count)
    {
        my_rank = omp_get_thread_num();
#pragma omp for schedule(static, 1)
        for (i = 0; i < line_count; i++)
        {
            j = 0;
            my_token = strtok_r_mod(lines[i], " \t\n,", &my_line);

            char tokens_concatenados[1024] = ""; 
            while (my_token != NULL)
            {
                if (j > 0)
                {
                    strcat(tokens_concatenados, " -- ");
                }
                strcat(tokens_concatenados, my_token);
                my_token = strtok_r_mod(NULL, " \t\n,", &my_line);
                j++;
            }

            printf("Thread %d terminou a linha -> %se os tokens foram -> %s\n\n",
                   my_rank, lines[i], tokens_concatenados);

            free(my_line);
        }
    }
    free_memory(lines, &line_count);
}

void get_text(char *lines[], int *qnt_line)
{
    char *line;
    while ((line = (char *)malloc(sizeof(char) * MAX_LINE)) && fgets(line, MAX_LINE, stdin))
    {
        lines[*qnt_line] = line;
        (*qnt_line)++;
    }
    free(line);
}

void free_memory(char *lines[], int *qnt_line)
{
    for (int i = 0; i < *qnt_line; i++)
    {
        free(lines[i]);
    }
    free(lines);
    *qnt_line = 0;
}

char *strtok_r_mod(const char *text, const char *delim, char **my_line)
{
    int start = 0, end = 0;

    if (text != NULL)
    {
        *my_line = malloc(strlen(text) + 1);
        if (!*my_line)
        {
            exit(1);
        }
        strcpy(*my_line, text);
    }

    int str_len = strlen(*my_line);
    while (start < str_len && strchr(delim, (*my_line)[start]))
    {
        start++;
    }
    if (start == str_len)
    {
        *my_line = NULL;
        return NULL;
    }

    for (end = start; end < str_len; end++)
    {
        if (strchr(delim, (*my_line)[end]))
        {
            break;
        }
    }
    int tok_len = end - start;
    char *tok = malloc(tok_len + 1);
    if (!tok)
    {
        exit(1);
    }
    strncpy(tok, *my_line + start, tok_len);
    tok[tok_len] = '\0';

    *my_line += end;
    return tok;
}
