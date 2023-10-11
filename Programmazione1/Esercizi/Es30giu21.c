#include <stdio.h>
#define DIM 30

int carica(int v[], char nome[]);
void visualizza(int v[]);
void somme(int v[], int *s1, int *s2);
void cancella(int v[]);

/*La funzione main che
• riceve in ingresso il nome di un file da riga di comando. In caso contrario mostra un
opportuno messaggio di errore e termina.
• Dichiara un vettore di interi, di dimensione 30.
• Invoca la funzione per il caricamento del vettore da file.
• Se il caricamento fallisce, mostra un opportuno messaggio di errore e termina.
• Se il caricamento ha successo
• invoca la funzione per visualizzare il contenuto del vettore.
• Invoca la funzione per le somme e ne visualizza i risultati tramite opportuni
messaggi.
• Invoca la funzione per cancellare un elemento del vettore.
• Invoca di nuovo la funzione per visualizzare il contenuto del vettore.*/
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore, esecuzione del file errata\n");
    }
    else
    {
        int vet[DIM], c, somma1, somma2;

        c = carica(vet, argv[1]);
        if (c == 0)
        {
            printf("Errore, Il file selezionato non esiste\n");
        }

        else
        {
            visualizza(vet);
            somme(vet, &somma1, &somma2);
            printf("la somma dei valori composti da una cifra e' %d\n", somma1);
            printf("La somma dei valori composti da una cifra e' %d\n", somma2);
            cancella(vet);
            visualizza(vet);
        }
    }
    return 1;
}

/*Una funzione che
- riceve in ingresso un vettore di numeri interi e il nome di un file di testo.
- Tenta di aprire il file.
- Se l’apertura fallisce, restituisce 0.
- Se l’apertura ha successo
- copia dal file al vettore i valori strettamente positivi e dispari (si assume che il
    file contenga una quantità di valori inferiore alla dimensione del vettore).
- Chiude il file.
- Mette il valore -1 come “tappo” del vettore.
- Restituisce 1.*/
int carica(int v[], char nome[])
{
    int i, x, esito;
    FILE *fp;

    fp = fopen(nome, "r");
    if (fp == NULL)
    {
        esito = 0;
    }
    else
    {
        i = 0;
        while (fscanf(fp, "%d", &x) != EOF)
            if (x > 0 && x % 2 == 1)
            {
                v[i] = x;
                i++;
            }
        fclose(fp);

        v[i] = -1;
        esito = 1;
    }
    return esito;
}

/*Una funzione che
- riceve in ingresso un vettore di numeri interi con -1 come “tappo”.
- Visualizza indici e valori del vettore disponendoli verticalmente, come nell’esempio.
- Esempio: indici   valori
            0       21
            1       7
            2       11
            3       5
            4       11
            5       9
- Non restituisce niente.*/
void visualizza(int v[])
{
    int i;

    printf("\nindici\tvalori\n");
    for (i = 0; v[i] != -1; i++)
        printf("%d\t%d\n", i, v[i]);
    printf("\n");
}

/*Una funzione che
- riceve in ingresso un vettore (v) di numeri interi con -1 come “tappo”, e due variabili (s1, s2).
- Assegna a s1 la somma dei valori composti da una cifra, presenti in v.
- Assegna a s2 la somma dei valori composti da due cifre, presenti in v.
- Non restituisce niente.
- Esempio: v: 21 7 11 5 11 9 ---> s1: 21 s2: 43*/
void somme(int v[], int *s1, int *s2)
{
    int i;
    *s1 = 0;
    *s2 = 0;

    for (i = 0; v[i] != -1; i++)
    {
        if (v[i] >= 0 && v[i] <= 9)
            *s1 += v[i];

        else
        {
            if (v[i] >= 10 && v[i] <= 99)
                *s2 += v[i];
        }
    }
}

/*Una funzione che
• riceve in ingresso un vettore (v) di numeri interi con -1 come “tappo”.
• Cancella il primo elemento di v mantenendo tutti gli altri elementi.
    Esempio: v: 21 7 11 5 11 9 ---> v: 7 11 5 11 9
• Non restituisce niente.*/
void cancella(int v[])
{
    int i;

    for (i = 0; v[i] != -1; i++)
    {
        v[i] = v[i + 1];
    }
}