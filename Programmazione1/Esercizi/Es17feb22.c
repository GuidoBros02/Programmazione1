#include <stdio.h>
#include <string.h>
#define DIM 30

int carica(char s[]);
void calcola(char s[], int h, int *p1, int *p2);
int modifica(char s[], int h, char c, int d);
void stampa(char s[], int h, char nome[]);

/*La funzione main che
• deve ricevere in ingresso (da linea di comando) un solo parametro, cioè il nome di un file. In caso
    contrario visualizza un opportuno messaggio di errore e termina.
    Esempio: esercizio.out stringa.txt
• Dichiara un vettore di caratteri di dimensione costante 30.
• Invoca la funzione per inserire la stringa nel vettore; quindi visualizza la stringa e la sua lunghezza.
• Invoca la funzione per il conteggio dei caratteri; quindi ne visualizza i risultati.
• Chiede all’utente di inserire un carattere e un indice; invoca la funzione per l’inserimento del carattere
    nella stringa; visualizza la stringa aggiornata e la sua lunghezza.
• Invoca la funzione per la scrittura parziale della stringa su file (il nome del file è quello ricevuto da linea
    di comando)*/
int main(int argc, char *argv[])
{
    char vet[DIM], car;
    int lunghezza, vocali, cifre, pos;

    if (argc != 2)
    {
        printf("Errore nella compilazione, inserire anche il nome del file.\n");
    }
    else
    {
        lunghezza = carica(vet);
        printf("La stringa e' %s e contiene %d caratteri.\n", vet, lunghezza);
        calcola(vet, lunghezza, &vocali, &cifre);
        printf("\nLa stringa contiene %d vocali minuscole e %d cifre.\n", vocali, cifre);
        printf("\nInserire un carattere da aggiungere alla stringa: ");
        scanf("\n%c", &car);
        printf("Inserire la posizione dove aggiungere il carattere: ");
        scanf("%d", &pos);
        lunghezza = modifica(vet,lunghezza, car, pos);
        printf("La stringa e' %s e contiene %d caratteri.\n\n", vet, lunghezza);
        stampa(vet, lunghezza, argv[1]);
    }
    return 1;
}

/*Una funzione
• che riceve in ingresso un vettore di caratteri.
• Chiede all’utente di inserire una stringa e la memorizza nel vettore di caratteri.
• La stringa deve contenere un numero pari di caratteri. In caso contrario visualizza un opportuno
messaggio di errore e ripete la richiesta di inserimento della stringa.
Esempi: stringa: hEllo.44 ---> 8 caratteri ---> OK
        stringa: hEllo.4 ---> 7 caratteri ---> ERRORE
• Restituisce la lunghezza della stringa.*/
int carica(char s[])
{
    int h, c;

    do
    {
        printf("Inserire una stringa composta da un numero pari di caratteri: ");
        scanf("%s", s);
        h=(int)strlen(s);

        c = h % 2 == 1;

        if (c)
            printf("Errore, la stirnga con contiene un numero pari di caratteri\n");
    } while (c);
    return h;
}

/*Una funzione che
• riceve in ingresso una stringa (s), la sua lunghezza, due parametri (p1, p2).
• Calcola e memorizza in p1 la quantità di vocali minuscole presenti in s.
• Calcola e memorizza in p2 la quantità di cifre presenti in s.
Esempio: s: hEllo.44 ---> p1: 1 p2: 2
• Non restituisce niente*/
void calcola(char s[], int h, int *p1, int *p2)
{
    int i;

    *p1 = 0;
    *p2 = 0;

    for (i = 0; i < h; i++)
    {

        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
            (*p1)++;
        if (s[i] >= '0' && s[i] <= '9')
            (*p2)++;
    }
}

/*Una funzione che
• riceve riceve in ingresso una stringa (s), la sua lunghezza (h), un carattere (c), un indice (d).
• Se d non supera h, inserisce c in s, in posizione d, mantenendo gli altri caratteri presenti in s.
Esempio: s: hEllo.44 c: $ d:2 ---> s: hE$llo.44
• Se d supera h allora non modifica la stringa.
Esempio: s: hEllo.44 c: $ d:10 ---> s: hEllo.44
• Restituisce la lunghezza aggiornata della stringa.*/
int modifica(char s[], int h, char c, int d)
{
    int i;

    if (d <= h)
    {
        for (i = h + 1; i > d; i--)
        {
            s[i] = s[i - 1];
        }
        s[d] = c;
        h++;
    }
    return h;
}

/*Una funzione che
• riceve in ingresso una stringa, la sua lunghezza, il nome di un file.
• Apre il file con quel nome.
• Scrive su file la prima metà della stringa.
Esempio: stringa: hE$llo.44 ---> file: hE$l
• Chiude il file.
• Non restituisce niente*/
void stampa(char s[], int h, char nome[])
{
    FILE *fp;
    int i;

    fp = fopen(nome, "w");

    h = h / 2;

    for (i = 0; i < h; i++)
    {
        fprintf(fp, "%c", s[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
}