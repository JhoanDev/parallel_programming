#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 15000

// Declarando os arrays globais
double A[MAX][MAX], x[MAX], y[MAX];

// Função para inicializar os arrays
void initialize() {
    for (int i = 0; i < MAX; i++) {
        x[i] = 1.0;  // Por exemplo, inicializando x com valores 1.0
        y[i] = 0.0;  // Inicializando y com zeros
        for (int j = 0; j < MAX; j++) {
            A[i][j] = 1.0;  // Inicializando A com valores 1.0
        }
    }
}

int main() {
    // Variáveis para medir o tempo
    clock_t start, end;
    double cpu_time_used;

    // Inicializa os arrays
    initialize();

    // Medindo o tempo do primeiro par de loops
    start = clock();
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo do primeiro par de loops: %f segundos\n", cpu_time_used);

    // Inicializando y novamente para garantir que o valor seja zero
    for (int i = 0; i < MAX; i++) {
        y[i] = 0.0;
    }

    start = clock();
    for (int j = 0; j < MAX; j++) {
        for (int i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo do segundo par de loops: %f segundos\n", cpu_time_used);

    return 0;
}
