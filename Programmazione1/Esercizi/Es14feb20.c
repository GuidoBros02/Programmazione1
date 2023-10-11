#include <stdio.h>
#define DIM 30

void carica(int v[], FILE *fp);
void visualizza(int v[]);
int cerca(int v[], int x);
void inserisci(int *v, int *x);

/*La funzione main che
• riceve in ingresso il nome di un file da riga di comando. In caso contrario mostra un
opportuno messaggio di errore e termina.
• Dichiara un vettore di interi, di dimensione 30.
• Apre il file con il nome ricevuto in ingresso. Se il file non esiste mostra un opportuno
messaggio di errore e termina.
• Invoca la prima funzione per caricare il vettore da file e chiude il file.
• Invoca la seconda funzione per visualizzare il contenuto del vettore.
• Richiede all’utente di inserire un valore da cercare nel vettore, invoca la funzione di
ricerca e ne visualizza il risultato tramite un opportuno messaggio.
• Richiede all’utente di inserire un valore da inserire nel vettore, invoca la funzione di
inserimento e invoca di nuovo la funzione per visualizzare il vettore.*/
int main(int argc, char *argv[])
{
    int vet[DIM], val1, val2, pos;
    FILE *fp;
    if (argc < 2)
        printf("\nERRORE: manca il nome del file di dati.\n\n");
    else
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
            printf("\nERRORE: il file non esiste.\n\n");
        else
        {
            carica(vet, fp);
            fclose(fp);
            visualizza(vet);
            printf("\nInserire un valore da cercare: ");
            scanf("%d", &val1);
            pos = cerca(vet, val1);
            if (pos == -1)
                printf("Valore assente.\n");
            else
                printf("Valore presente in posizione %d (prima occorrenza).\n", pos);
            printf("\nInserire un valore da mettere all'inizio: ");
            scanf("%d", &val2);
            inserisci(vet, &val2);
            visualizza(vet);
        }
    }
    return 1;
}

/*Una funzione che
- riceve in ingresso un vettore di numeri interi e un puntatore a file.
- Carica nel vettore i valori strettamente positivi e dispari contenuti nel file (si assume
    che il file contenga una quantità di valori inferiore alla dimensione del vettore).
- Mette il valore -1 come “tappo” del vettore.
- Non restituisce niente.*/
void carica(int v[], FILE *fp)
{
    int i, x;
    i = 0;
    while (fscanf(fp, "%d", &x) != EOF)
    {
        if (x > 0 && (x % 2) == 1)
        {
            v[i] = x;
            i++;
        }
    }
    v[i] = -1;
}

/*Una funzione che
- riceve in ingresso un vettore di numeri interi con -1 come “tappo”.
- Visualizza indici e valori del vettore disponendoli verticalmente.
- Esempio: indici valori
            0       21
            1       7
            2       11
            3       5
            4       11
            5       9
- Non restituisce niente*/
void visualizza(int v[])
{
    int i;
    printf("indici\tvalori\n");
    for (i = 0; v[i] != -1; i++)
    {
        printf("%d\t%d\n", i, v[i]);
    }
    printf("\n");
}

/*Una funzione che
- riceve in ingresso un vettore (v) di numeri interi con -1 come “tappo”, e un valore
    intero (x).
- Se x è presente nel vettore, restituisce l’indice della prima occorrenza di x nel
    vettore.
- Se x è assente, restituisce -1.
- Esempi:   v: 21 7 11 5 11 9 x: 11 ---> indice: 2
            v: 21 7 11 5 11 9 x: 31 ---> indice: -1*/
int cerca(int v[], int x)
{
    int i;
    int ris = -1;
    for (i = 0; v[i] != -1 && ris == -1; i++)
        if (v[i] == x)
            ris = i;

    return ris;
}

/*Una funzione che
• riceve in ingresso un vettore (v) di numeri interi con -1 come “tappo”, e un valore
intero (x).
• Inserisce x all’inizio del vettore mantenendo tutti i valori caricati in precedenza.
Esempio: v: 21 7 11 5 11 9 x: 23 ---> v: 23 21 7 11 5 11 9
• Non restituisce niente.
• Facoltativo: ricevere e gestire v e x tramite puntatori.*/
void inserisci(int *v, int *x)
{
    int i, len;
    len = 0;
    while (*(v + len) != -1)
        len++;
    for (i = len; i >= 0; i--)
        *(v + i + 1) = *(v + i);
    *v = *x;
}