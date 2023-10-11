#include <stdio.h>
#define DIM 30

int carica(int v[], char nome[], int x);
void visualizza(int v[]);
void cerca(int v[], int*d1, int*d2);
void copia(int v1[], int v2[]);

/*La funzione main che
• deve ricevere in ingresso (da linea di comando) un solo parametro, cioè il nome di un file. In caso
contrario, visualizza un opportuno messaggio di errore e termina.
Esempio: ./esercizio.out valori.txt
• Dichiara due vettori di interi, ciascuno di 30 elementi.
• Chiede all’utente di inserire un valore intero e invoca la funzione per caricare il primo vettore da file. Se
il vettore non è stato caricato visualizza un opportuno messaggio di errore e termina.
• Invoca la funzione per visualizzare il primo vettore.
• Invoca la funzione per cercare i valori nel primo vettore. Ne visualizza il risultato tramite un opportuno
messaggio.
• Invoca la funzione per la copia parziale del primo vettore nel secondo vettore.
• Invoca la funzione per visualizzare il secondo vettore*/
int main(int argc, char *argv[])
{
    int vet1[DIM], vet2[DIM], a, car, primo, ultimo;

    if(argc!=2)
    {
        printf("\nErrore nella riga di comando.\n");
    }
    else
    {
        printf("\nInserire un valore intero: ");
        scanf("%d", &a);
        car=carica(vet1, argv[1], a);

        if(car)
        {
            visualizza(vet1);
            cerca(vet1, &primo, &ultimo);

            if(primo==-1 && ultimo==-1)
                printf("Nessun valore pari.\n");
            else
            {
                if(primo==ultimo)
                {
                    printf("Un solo valore è pari. Il valore in questione è %d e sitrova in posizione %d.\n", vet1[primo], primo);
                }
                else
                {
                    printf("Il primo valore pari %d si strova in posizione %d.\n",vet1[primo], primo);
                    printf("L'ultimo valore pari è %d e si trova in posizione %d.\n", vet1[ultimo], ultimo);
                }
            copia(vet1, vet2);
            visualizza(vet2);
            }
        }
        else
        {
            printf("\nErrore nell'apertura del file.\n");
        }
    }
    return 1;
}

/*Una funzione
• che riceve in ingresso un vettore di interi (v), il nome di un file, e un valore intero (x).
• Tenta di aprire il file con quel nome.
• Se il file non esiste restituisce 0.
• Se il file esiste
• copia dal file al vettore i valori positivi e multipli di x.
• Mette il valore -1 come “tappo” del vettore.
 Esempio: file: -3 2 3 7 -6 5 15 27 30 6 18 8 21 x: 3 ---> v: 3 15 27 30 6 18 21
• Chiude il file.
• Restituisce 1*/
int carica(int v[], char nome[], int x)
{
    int i, esito, val;

    FILE *fp;
    fp = fopen(nome, "r");
    if (fp == NULL)
    {
        esito = 0;
    }
    else
    {
        i = 0;
        while (fscanf(fp, "%d", &val) != EOF && i < DIM - 1)
            if (val > 0 && val % x == 0)
            {
                v[i] = val;
                i++;
            }
        v[i] = -1;
        fclose(fp);
        esito = 1;
    }
    return esito;
}

/*Una funzione che
• riceve in ingresso un vettore di interi con “tappo”.
• Se il vettore non è vuoto visualizza indici e valori su due righe come mostrato nell’esempio.
Esempio:
indici 0 1 2 3 4 5 6
valori 3 15 27 30 6 18 21
• Se il vettore è vuoto mostra il messaggio “vettore vuoto”.
• Non restituisce niente. */
void visualizza(int v[])
{
    int i;

    if(v[0]!=-1)
    {
        printf("\nindici:\t");
        for(i=0; v[i]!=-1; i++)
            printf("%d\t", i);

        printf("\nValori:\t");
        for(i=0; v[i]!=-1; i++)
            printf("%d\t", v[i]);
        printf("\n\n");
    }
    else
    {
        printf("\nErrore: vettore vuoto.\n\n");
    }
}

/*Una funzione che
• riceve in ingresso un vettore di interi con “tappo” (v) e due indici (d1, d2).
• Memorizza in d1 l’indice del primo valore pari nel vettore. Se assente, memorizza -1.
• Memorizza in d2 l’indice dell’ultimo valore pari nel vettore. Se assente, memorizza -1.
Esempi:     v: 3 15 27 30 6 18 21 ---> d1: 3 d2: 5
            v: 3 15 27 30 9 15 21 ---> d1: 3 d2: 3
            v: 3 15 27 33 9 15 21 ---> d1: -1 d2: -1
• Non restituisce nulla.*/
void cerca(int v[], int*d1, int*d2)
{
    int i;

    *d1=-1;
    *d2=-1;

    for(i=0; v[i]!=-1; i++)
        if(v[i]%2==0)
        {
            if(*d1==-1)
                *d1=i;
            *d2=i;
        }
}

/*Una funzione che
• riceve in ingresso un vettore di interi con “tappo” (v1) e un vettore di interi (v2).
• Copia in v2 la prima metà dei valori presenti in v1.
Esempio: v1: 3 15 27 30 6 18 21 ---> v2: 3 15 27
• Mette il valore -1 come “tappo” di v2.
• Non restituisce niente.*/
void copia(int v1[], int v2[])
{
    int i, j;

    j=0; 

    while(v1[j]!=-1)
        j++;
    j=j/2;

    for(i=0; i<j; i++)
        v2[i]=v1[i];
    v2[i]=-1;
}