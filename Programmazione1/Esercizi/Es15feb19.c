#include <stdio.h>
#include <string.h>
#define NUM_STR 300
#define NUM_CAR 30

int carica(char s[][NUM_CAR], char nome[]);
void visualizza(char s[][NUM_CAR], int x);
int cerca(char s[][NUM_CAR], int x, char parola[]);
int calcola(char s[][NUM_CAR], int x);

/*La funzione main che
• riceve in ingresso il nome di un file (da riga di comando).
• Dichiara un vettore di 300 stringhe dove ogni stringa può contenere 30
    caratteri al massimo.
• Invoca la prima funzione per caricare il vettore da file.
• Invoca la seconda funzione per visualizzare il contenuto del vettore.
• Chiede all’utente di inserire una parola. Quindi invoca la terza funzione per
    ricercare la parola nel vettore. Ne visualizza il risultato tramite un opportuno messaggio.
• Invoca la quarta funzione per il conteggio e ne visualizza il risultato tramite un
    opportuno messaggio.
• Facoltativo: gestire i casi in cui il nome del file non esiste o non viene indicato
    da riga di comando, mostrando i rispettivi messaggi di errore.*/
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore nella compilazione da terminale, inserire nome del File\n");
        return 1;
    }
    else
    {
        char str[NUM_STR][NUM_CAR], r[NUM_CAR];
        int parole, ris, v;
        parole = carica(str, argv[1]);
        visualizza(str, parole);
        printf("Inserisci una parola: ");
        scanf("%s", r);
        ris = cerca(str, parole, r);
        if (ris == 1)
        {
            printf("La parola %s è presente\n", r);
        }
        else
        {
            printf("La parola %s è assente\n", r);
        }
        v = calcola(str, parole);
        printf("Sono presenti %d parole che iniziano per vocale\n\n", v);
        return 0;
    }
}

/*Una funzione che
- riceve in ingresso un vettore di stringhe e il nome di un file.
- Apre il file.
- Carica nel vettore le parole contenute nel file.
- Calcola la quantità di parole caricate.
- Chiude il file.
- Restituisce tale quantità.
- Facoltativo: gestire il caso in cui non esiste il file con quel nome, ritornando -1.*/
int carica(char s[][NUM_CAR], char nome[])
{
    int i;
    FILE *fp;
    fp = fopen(nome, "r");

    if (fp == NULL)
    {
        printf("Errore, non esiste il file\n");
        i = -1;
    }
    else
    {
        i = 0;
        while (fscanf(fp, "%s", s[i]) != EOF)
        {
            printf("%s\n", s[i]);
            i++;
        }
    }
    fclose(fp);
    printf("\n");

    return i;
}

/*Una funzione che
- riceve in ingresso un vettore di stringhe e la quantità di stringhe in esso
    contenute.
- Visualizza il contenuto del vettore seguendo la notazione indice: parola e
    mostrando 3 parole per riga. 
    Esempio:
    0: Quel 1: ramo 2: del
    3: lago 4: di 5: Como,
    6: che 7: volge 8: a
    ...
- Non restituisce niente*/
void visualizza(char s[][NUM_CAR], int x)
{
    int i;
    printf("\n");
    for (i = 0; i < x; i++)
    {
        printf("%d: %s\t", i, s[i]);
        if ((i + 1) % 3 == 0)
            printf("\n");
    }
    printf("\n\n");
}

/*Una funzione che
- riceve in ingresso un vettore di stringhe, la quantità di stringhe in esso
    contenute, ed una parola.
- Ricerca la parola nel vettore (Suggerimento: strcmp).
- Restituisce 1 se la parola è presente; restituisce 0 se la parola è assente*/
int cerca(char s[][NUM_CAR], int x, char parola[])
{
    int i, esito;
    esito = 0;
    for (i = 0; i < x && esito == 0; i++)
    {
        if (strcmp(parola, s[i]) == 0)
            esito = 1;
    }
    return esito;
}

/*Una funzione che
• riceve in ingresso un vettore di stringhe e la quantità di stringhe in esso
contenute.
• Calcola il numero di parole che iniziano con una vocale (maiuscola o
minuscola).
• Restituisce tale numero.*/
int calcola(char s[][NUM_CAR], int x)
{
    int i, n;
    n = 0;

    for (i = 0; i < x; i++)
    {
        if (s[i][0] == 'a' || s[i][0] == 'e' || s[i][0] == 'i' || s[i][0] == 'o' || s[i][0] == 'u' ||
            s[i][0] == 'A' || s[i][0] == 'E' || s[i][0] == 'I' || s[i][0] == 'O' || s[i][0] == 'U')
            n++;
    }
    return n;
}
