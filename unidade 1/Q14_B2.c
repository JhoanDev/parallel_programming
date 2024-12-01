#include <math.h>
#include <stdio.h>

int main()
{
    double t_sequencial = 100;
    double t_paralelo;
    double speedup;
    double eficiencia;
    double overhead = 3;
    int p = 16;

    FILE *file = fopen("tabela_Q14B2.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(file, "%-5s%-15s%-17s%-35s%-15s%-15s\n", "p", "Overhead(*2)", "Sequencial(*1,5)", "((Sequencial/p)+Overhead)", "Speedup", "Eficiência");

    for (int i = 0; i < 30; i++)
    {
        t_paralelo = (t_sequencial / p) + overhead;
        speedup = t_sequencial / t_paralelo;
        eficiencia = speedup / p;

        fprintf(file, "%-5d%-15.2f%-17.2f%-35.2f%-15.2f%-15.2f\n", p, overhead, t_sequencial, t_paralelo, speedup, eficiencia);

        t_sequencial *= 1.5;
        overhead *= 2;
    }

    fclose(file);

    return 0;
}
