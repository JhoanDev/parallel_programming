#include <math.h>
#include <stdio.h>

int main() {
    double t_sequencial;
    double t_paralelo;
    double speedup;
    double eficiencia;
    int n = 10;
    int p = 1;

    FILE *file = fopen("tabela_Q14A.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1; 
    }

    fprintf(file, "%-5s%-5s%-20s%-20s%-15s%-15s\n", "n", "p", "Tempo Sequencial", "Tempo Paralelo", "Speedup", "Eficiência");

    while (n <= 360)
    {
        p = 1;
        while (p <= 128)
        {
            t_sequencial = pow(n, 2);
            t_paralelo = pow(n, 2) / p + log2(p);
            speedup = t_sequencial / t_paralelo;
            eficiencia = speedup / p;

            fprintf(file, "%-5d%-5d%-20.2f%-20.2f%-15.2f%-15.2f\n", n, p, t_sequencial, t_paralelo, speedup, eficiencia);

            p *= 2; 
        }
        fprintf(file, "\n");
        n *= 2; 
    }

    fclose(file);


    return 0;
}
