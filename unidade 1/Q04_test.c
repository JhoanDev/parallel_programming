#include <stdio.h>

#define NUCLEOS 8

int main(){

    int div = 2;
    int salto = 1;
    int aux = 1;

    int recebe;
    int envia;
    for (int i = NUCLEOS >> 1; i != 0; i = i >> 1)
    {
        printf("\nEtapa: %d\n", aux++);
        for (int j = 0; j < NUCLEOS; j++)
        {
            if (j % div == 0)
            {
                printf("Núcleo %d recebe de %d\n", j, j ^ salto);
            }
            else if (j % salto == 0)
            {
                printf("Núcleo %d envia para %d\n\n", j, j ^ salto);
            }
        }
        div = div << 1;
        salto = salto << 1;
    }

    return 0;
}