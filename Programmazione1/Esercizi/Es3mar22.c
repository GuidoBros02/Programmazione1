#include <stdio.h>
#include <string.h>
#define DIM 30

int carica(char v[][DIM], char nome[]);
void visualizza(char v[][DIM], int q);
void calcola(char v[][DIM], int q, char x, int *d1, int *d2);
int cancella(char v[][DIM], int q);

/*La funzione main che
• deve ricevere in ingresso (da linea di comando) un solo parametro, cioè il nome di un file. In caso
contrario, visualizza un opportuno messaggio di errore e termina.
Esempio: ./esercizio.out stringhe.txt
• Dichiara un vettore di 30 stringhe, ciascuna di 30 caratteri.
• Invoca la funzione per caricare il vettore da file. Se il file non esiste visualizza un messaggio di errore e
termina.
• Invoca la funzione per visualizzare il vettore.
• Chiede all’utente di inserire un carattere.
• Invoca la funzione che ricerca le parole con tale carattere e ne visualizza il risultato tramite un
opportuno messaggio.
• Invoca la funzione per cancellare una stringa e invoca di nuovo la funzione per visualizzare il vettore.*/
int main(int argc, char *argv[])
{
    char vet[DIM][DIM], car;
    int num, prima, ultima;

    if (argc != 2)
    {
        printf("Errore nella compilazione su riga di comando.\n");
    }
    else
    {
        num = carica(vet, argv[1]);

        if (num == -1)
            printf("\nErrore, il file non esiste.\n");
        else
        {
            visualizza(vet, num);
            printf("Inserire un carattere: ");
            scanf("%c", &car);
            calcola(vet, num, car, &prima, &ultima);
            if (prima == -1 && ultima == -1)
                printf("Nessuna parola finisce con '%c'.\n", car);
            else 
                if (prima == ultima)
                    printf("Una sola parola (%s) finisce con '%c' e ha indice %d.\n", vet[prima], car, prima);
                else
            {
                printf("La prima parola (%s) che finisce con '%c' ha indice %d.\n", vet[prima], car, prima);
                printf("L'ultima parola (%s) che finisce con '%c' ha indice %d.\n", vet[ultima], car, ultima);
            }
            num = cancella(vet, num);
            visualizza(vet, num);
        }
    }
    return 1;
}

/*Una funzione
• che riceve in ingresso un vettore di stringhe e il nome di un file.
• Tenta di aprire il file con quel nome.
• Se il file non esiste restituisce -1.
• Se il file esiste
• copia dal file al vettore le stringhe che contengono almeno 3 vocali minuscole.
 Esempio: file: Alessandria Asti Novara Vercelli Torino Como Milano
vettore: Alessandria Novara Vercelli Torino Milano
• Chiude il file.
• Restituisce il numero di stringhe copiate nel vettore.*/
int carica(char v[][DIM], char nome[])
{
    FILE *fp;
    int c, q, l, i, j;
    char parola[DIM];

    fp = fopen(nome, "r");
    if (fp == NULL)
        q = -1;
    else
    {
        j = 0;
        while (fscanf(fp, "%s", parola) != EOF && j < DIM)
        {
            l = (int)strlen(parola);
            c = 0;

            for (i = 0; i < l; i++)
                if (parola[i] == 'a' || parola[i] == 'e' || parola[i] == 'i' ||
                    parola[i] == 'o' || parola[i] == 'u')
                    c++;
            if (c >= 3)
            {
                strcpy(v[j], parola);
                j++;
            }
        }
        fclose(fp);
        q = j;
    }
    return q;
}

/* Una funzione che
• riceve in ingresso un vettore di stringhe e la quantità di stringhe che contiene.
• Visualizza indici e stringhe su due righe come mostrato nell’esampio.
Esempio:
indici   0           1      2        3      4
stringhe Alessandria Novara Vercelli Torino Milano
• Non restituisce niente. */
void visualizza(char v[][DIM], int q)
{
    int i, l;

    printf("\nINDICE:\t\t");

    for (i = 0; i < q; i++)
    {
        printf("%d\t\t", i);
    }

    printf("\nSTRINGHE:\t");

    for (i = 0; i < q; i++)
    {
        printf("%s\t", v[i]);
        l = (int)strlen(v[i]);

        if (l <= 7)
        {
            printf("\t");
        }
    }
    printf("\n\n");
}

/* Una funzione che
• riceve in ingresso un vettore di stringhe, la quantità di stringhe che contiene, un carattere, due indici
(d1, d2).
• Memorizza in d1 l’indice della prima parola che finisce con tale carattere. Se assente, memorizza -1.
• Memorizza in d2 l’indice dell’ultima parola che finisce con tale carattere. Se assente, memorizza -1.
Esempio: Alessandria Novara Vercelli Torino Milano
carattere: a ---> d1: 0 d2: 1
carattere: o ---> d1: 3 d2: 4
carattere: i ---> d1: 2 d2: 2
carattere: u ---> d1: -1 d2: -1
• Non restituisce nulla.*/
void calcola(char v[][DIM], int q, char c, int *d1, int *d2)
{
    int i, j;

    *d1 = -1;
    *d2 = -1;

    for (i = 0; i < q; i++)
    {
        j = (int)strlen(v[i]) - 1;
        if (c == v[i][j])
        {
            if (*d1 == -1)
                *d1 = i;
            *d2 = i;
        }
    }
}

/*Una funzione che
• riceve in ingresso un vettore di stringhe e la quantità di stringhe che contiene.
• Cancella dal vettore la prima stringa mantenendo tutte le altre.
Esempio: Alessandria Novara Vercelli Torino Milano ---> Novara Vercelli Torino Milano
• Restituisce la quantità di stringhe aggiornata.*/
int cancella(char v[][DIM], int q)
{
    int i;

    for (i = 0; i < q - 1; i++)
    {
        strcpy(v[i], v[i + 1]);
    }
    v[i][0] = '\0';
    q--;

    return q;
}