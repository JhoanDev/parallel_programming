#include <stdio.h>
#include <stdlib.h>

void prefixed_sum_serial(double **prefixed_sum, double **vet, int n)
{
    int i;
    double sum = 0.0;
    for (i = 0; i < n; i++)
    {
        sum += (*vet)[i];
        (*prefixed_sum)[i] = sum;
    }
}

void print_vector(double *vector, int n){
    int i;
    printf("\nVetor: ");
    for (i = 0; i < n; i++)
    {
        printf("%.1lf ", vector[i]);
    }
    printf("\n");
}

int main(void)
{
    int n, i;
    double *vet_sum, *vet;

    printf("insira a quantidade de elementos do vetor: ");
    scanf("%d", &n);

    vet_sum = (double *)malloc(sizeof(double) * n);
    vet = (double *)malloc(sizeof(double) * n);

    printf("Insira os elementos do vetor: ");
    for (i = 0; i < n; i++)
        scanf("%lf", &vet[i]);

    prefixed_sum_serial(&vet_sum, &vet, n);
    print_vector(vet_sum, n);

    free(vet);
    free(vet_sum);
    return 0;
}