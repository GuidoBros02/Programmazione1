#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIM 3

void carica(int m[][DIM], int a, int b);
void visualizza(int m[][DIM]);
void cerca(int m[][DIM], int x, int *r, int *c);
int salva(int m[][DIM], int r, char valori[]);

/*La funzione main che
• riceve in ingresso, da riga di comando, due valori interi positivi (il primo deve essere
minore del secondo) e il nome di un file. In caso contrario, mostra un opportuno
messaggio di errore e termina.
◦ Esempio: esercizio.out 1 9 valori.txt
• Dichiara una matrice quadrata (di dimensione costante, a scelta).
• Invoca la funzione per caricare la matrice passandole i due valori interi ricevuti in
ingresso.
• Invoca la funzione per visualizzare la matrice.
• Chiede all’utente di inserire il valore da cercare nella matrice. Invoca la funzione per
la ricerca. Visualizza il risultato (posizione o assente) tramite un opportuno
messaggio.
• Chiede all’utente di inserire l’indice di una riga. Invoca la funzione per la copia su file
della riga. Visualizza l’esito della funzione tramite un opportuno messaggio (indice
non compatibile / copia avvenuta / problemi con il file)*/
int main(int argc, char *argv[])
{
    int a, b, n, esito;
    srand(time(NULL));

    if (argc != 4)
    {
        printf("Numero di argomenti errato\n");
        return 1;
    }
    else
    {
        a = atoi(argv[1]);
        b = atoi(argv[2]);

        if (b <= a || a <= 0 || b <= 0)
        {
            printf("Errori! i numeri devono essere positivi, e il primo minore del secondo\n");
            return 1;
        }
        else
        {
            int matrice[DIM][DIM];
            int riga, colonna, r1;

            carica(matrice, a, b);
            visualizza(matrice);
            printf("Inserire numero da cercare nella matrice: ");
            scanf("%d", &n);
            cerca(matrice, n, &riga, &colonna);
            if (riga == -1 && colonna == -1)
            {
                printf("Il numero inserito non è presente\n");
            }
            else
            {
                printf("Il numero è presente in posizione %d, %d (Riga e colonna)\n", riga, colonna);
            }
            printf("Inserire indice di una riga da copiare: ");
            scanf("%d", &r1);
            esito = salva(matrice, r1, argv[3]);
            if (esito == 0)
            {
                printf("Il numero della riga selezionata non è valida\n");
            }
            if (esito == -1)
            {
                printf("il file non è presente\n");
            }
            if (esito == 1)
            {
                printf("La riga %d e' stata copiata correttamente nel file %s\n", r1, argv[3]);
            }
        }
    }
    return 0;
}

/*Una funzione che
• riceve in ingresso una matrice quadrata (m) composta da numeri interi, e due valori
interi (a, b).
• Carica in m dei valori casuali compresi tra a e b (inclusi).
• Non restituisce niente.
• Esempio: a: 1 b: 9 m: 3 5 1
                        2 7 9
                        4 2 8*/
void carica(int m[][DIM], int a, int b)
{
    int i, j;
    for (i = 0; i < DIM; i++)
    {
        for (j = 0; j < DIM; j++)
        {
            m[i][j] = rand() % (b - a + 1) + a;
        }
    }
}

/*Una funzione che
• riceve in ingresso una matrice quadrata (m) composta da numeri interi.
• Visualizza il contenuto di (m) in forma tabulata. Al termine di ogni riga visualizza la
somma dei valori su tale riga.
• Non restituisce niente.
- Esempio:  3 5 1 somma: 9
            2 7 9 somma: 18
            4 2 8 somma: 14*/
void visualizza(int m[][DIM])
{
    int s;
    int i, j;

    for (i = 0; i < DIM; i++)
    {
        s = 0;
        for (j = 0; j < DIM; j++)
        {
            printf("%d\t", m[i][j]);
            s = s + m[i][j];
        }
        printf("la somma è di: %d\n", s);
    }
}

/*Una funzione che
• riceve in ingresso una matrice quadrata (m) composta da numeri interi, un valore
intero (x), un indice di riga (r) e un indice di colonna (c).
• Cerca x in m, visitando m riga per riga.
• Se x non è presente in m, memorizza (-1,-1) in (r,c).
• Se x è presente in m, memorizza in (r,c) la posizione della prima occorrenza di x in m.
• Non restituisce niente.
 Esempio: m:   3 5 1
                2 7 9
                4 2 8   x:2 ----> r: 1 c: 0  */
void cerca(int m[][DIM], int x, int *r, int *c)
{
    int i, j;
    *r = -1;
    *c = -1;

    for (i = 0; i < DIM; i++)
    {
        for (j = 0; j < DIM; j++)
        {
            if (m[i][j]==x)  //(*(*(m + i) + j) == x)
            {
                *r = i;
                *c = j;
            }
        }
    }
}

/*Una funzione che
• riceve in ingresso una matrice quadrata (m) composta da numeri interi, l’indice di
una riga (r) e il nome di un file.
• Se r non è compatibile con la dimensione di m, restituisce 0.
• Se r è compatibile con la dimensione di m, allora apre il file, scrive su file il
contenuto della riga indicata da r, chiude il file, e restituisce 1.
• Se l’apertura del file non riesce, ritorna -1.
Esempio:    3 5 1
            2 7 9
            4 2 8       r:0 ----> file: 3 5 1 */
int salva(int m[][DIM], int r, char valori[])
{
    int i, j;
    int e;
    FILE *fp;
    if (r < 0 || r >= DIM)
        e = 0;

    else
    {
        fp = fopen(valori, "w");
        if (fp == NULL)
        {
            e = -1;
        }
        else
        {
            for (j = 0; j < DIM; j++)
                fprintf(fp, "%d\t", m[r][j]);
            fprintf(fp, "\n");

            fclose(fp);
            e = 1;
        }
    }
    return e;
}
