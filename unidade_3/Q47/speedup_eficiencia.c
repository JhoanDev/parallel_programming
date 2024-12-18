#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTRIES 100

typedef struct
{
    long long n;
    int p;
    double median;
} Data;

int main()
{
    FILE *input = fopen("output.txt", "r");
    FILE *output = fopen("speedup_efficiency.txt", "w");
    if (input == NULL || output == NULL)
    {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    Data entries[MAX_ENTRIES];
    int total_entries = 0;

    char line[256];
    fgets(line, sizeof(line), input);

    while (fgets(line, sizeof(line), input))
    {
        Data entry;
        if (sscanf(line, "%lld %d %lf", &entry.n, &entry.p, &entry.median) == 3)
        {
            entries[total_entries++] = entry;
        }
    }

    fprintf(output, "n\t\t\tp\tSpeedup\t\tEficiência\n");
    for (int i = 0; i < total_entries; i++)
    {
        if (entries[i].p == 1)
        {
            long long current_n = entries[i].n;
            double t1 = entries[i].median;

            for (int j = 0; j < total_entries; j++)
            {
                if (entries[j].n == current_n && entries[j].p > 1)
                {
                    double tp = entries[j].median;
                    double speedup = t1 / tp;
                    double efficiency = speedup / entries[j].p;

                    fprintf(output, "%lld\t%d\t%.6f\t%.6f\n",
                            entries[j].n, entries[j].p, speedup, efficiency);
                }
            }
        }
    }

    printf("Resultados salvos em 'speedup_efficiency.txt'.\n");

    fclose(input);
    fclose(output);
    return 0;
}
