#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 5
#define MAX_ENTRIES 100

typedef struct
{
    long long n;
    int p;
    double times[MAX_TIMES];
    int count;
} Data;

int compare(const void *a, const void *b)
{
    double diff = (*(double *)a) - (*(double *)b);
    return (diff > 0) - (diff < 0);
}

double calculate_mean(double times[], int count)
{
    double sum = 0.0;
    for (int i = 0; i < count; i++)
    {
        sum += times[i];
    }
    return sum / count;
}

double calculate_median(double times[], int count)
{
    qsort(times, count, sizeof(double), compare);
    if (count % 2 == 0)
    {
        return (times[count / 2 - 1] + times[count / 2]) / 2.0;
    }
    else
    {
        return times[count / 2];
    }
}

double find_min(double times[], int count)
{
    double min = times[0];
    for (int i = 1; i < count; i++)
    {
        if (times[i] < min)
        {
            min = times[i];
        }
    }
    return min;
}

int main()
{
    FILE *input = stdin;
    FILE *output = fopen("output.txt", "w");
    if (output == NULL)
    {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }

    Data entries[MAX_ENTRIES];
    int total_entries = 0;

    char line[256];
    long long n;
    int p;
    double time;

    while (fgets(line, sizeof(line), input))
    {
        if (sscanf(line, "Testing with n=%lld, p=%d...", &n, &p) == 2)
        {
            Data *current_entry = &entries[total_entries++];
            current_entry->n = n;
            current_entry->p = p;
            current_entry->count = 0;

            for (int i = 0; i < MAX_TIMES; i++)
            {
                if (fgets(line, sizeof(line), input) &&
                    sscanf(line, "Tempo decorrido = %lf", &time) == 1)
                {
                    current_entry->times[current_entry->count++] = time;
                }
            }
        }
    }

    fprintf(output, "n\t\t\tp\tMédia\t\tMediana\t\tMínimo\n");
    for (int i = 0; i < total_entries; i++)
    {
        double mean = calculate_mean(entries[i].times, entries[i].count);
        double median = calculate_median(entries[i].times, entries[i].count);
        double min = find_min(entries[i].times, entries[i].count);

        fprintf(output, "%lld\t%d\t%.6f\t%.6f\t%.6f\n",
                entries[i].n, entries[i].p, mean, median, min);
    }

    printf("Resultados salvos em 'output.txt'.\n");

    fclose(output);
    return 0;
}
