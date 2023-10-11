#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define DIM 11

int carica(int v[], int dim, int q)
{
    int i, e;
    e = 0;
    if (q >= 2 && q <= dim)
    {
        srand(time(NULL));

        for (i = 0; i < q; i++)
        {
            v[i] = rand() % (999 - 10 + 1) + 10;
            e = 1;
        }
    }
    v[i] = -1;
    return e;
}

void visualizza(int v[])
{
    int i;

    printf("\nIndici:\t");
    for (i = 0; v[i] != -1; i++)
    {
        printf("%d\t", i);
    }
    printf("\nValori:\t");
    for (i = 0; v[i] != -1; i++)
    {
        printf("%d\t", v[i]);
    }
    printf("\n\n");
}

void minimi(int v[], int *p1, int *p2)
{
    int i;

    *p1 = v[1];
    *p2 = v[0];
    for (i = 2; v[i] != -1; i++)
    {
        if (i % 2 == 1 && v[i] < *p1)
            *p1 = v[i];
        if (i % 2 == 0 && v[i] < *p2)
            *p2 = v[i];
    }
}

int copia(int v[], char nome[])
{
    FILE *fp;
    int i, conta;

    fp = fopen(nome, "w");
    conta = 0;
    for (i = 0; v[i] != -1; i++)
        if (v[i] >= 10 && v[i] <= 99)
        {
            fprintf(fp, "%d\t", v[i]);
            conta++;
        }
    fprintf(fp, "\n");
    fclose(fp);

    return conta;
}

int main(int argc, char*argv[])
{
    if(argc!=3)
    {
        printf("Errore, riga di comando non completa.\n");
        return 1;
    }
    else
    {
        int vet[DIM], car, cop, min1, min2;

        car=carica(vet, DIM, atoi(argv[1]));
        if(car==0)
        {
            printf("Errore, il vettore non è stato caricato.\n");
            return 1;
        }
        visualizza(vet);
        minimi(vet, &min1, &min2);
        printf("Il valore minimo in indice dispari è %d mentre in indice pari è %d.\n", min1, min2);
        cop=copia(vet, argv[2]);
        printf("I valori caricati sul file sono %d.\n\n", cop);
    }
    return 0;
}