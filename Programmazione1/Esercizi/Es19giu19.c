#include <stdio.h>
#define R 5
#define C 4

void carica(int m[R][C]);
void visualizza(int m[R][C]);
int cerca(int m[R][C], int n);
int somma(int m[R][C], int x);

/*La funzione main che
- riceve in ingresso il nome di un file (da riga di comando).
- Dichiara una matrice (usare delle costanti per le dimensioni).
- Invoca la funzione per il caricamento della matrice.
- Invoca la funzione che visualizza i valori nella matrice.
- Chiede all’utente di inserire un valore intero da ricercare nella matrice. Quindi invoca la
    funzione di ricerca.
- Chiede all’utente di inserire l’indice di una colonna. Quindi invoca la funzione per il
    calcolo della somma.
- Apre il file; scrive nel file degli opportuni messaggi con i risultati della ricerca e della
    somma; chiude il file.*/
int main(int argc, char *argv[])
{
    int mat[R][C];
    int x, ris, col, sum;
    FILE *fp;
    carica(mat);
    visualizza(mat);
    printf("Inserire un valore da cercare: ");
    scanf("%d", &x);
    ris = cerca(mat, x);
    printf("Inserire indice di una colonna: ");
    scanf("%d", &col);

    sum = somma(mat, col);
    if (argc > 1)
    {
        fp = fopen(argv[1], "w");
        if (fp != NULL)
        {
            if (ris == 0)
                fprintf(fp, "Il valore %d non è presente\n", x);
            else
                fprintf(fp, "Il valore '%d' e' presente\n", x);
            if (sum != -1)
                fprintf(fp, "La somma dei valori nella colonna '%d' e' %d\n", col, sum);
            else
                fprintf(fp, "Il valore '%d' della colonna non e' valido\n", col);
        }
        else
        {
            printf("Errore nell'apertura del file\n");
            return 1;
        }
        fclose(fp);

        return 0;
    }
}

/*Una funzione che
- riceve in ingresso una matrice di numeri interi.
- Chiede all’utente di inserire i valori della prima riga.
- Carica automaticamente i valori delle righe successive in questo modo: i valori su una
riga sono il doppio dei valori sulla riga precedente.
- Non restituisce niente.
Esempio con 5 righe e 4 colonne: 
    2 3 6 9
    4 6 12 18
    8 12 24 36
    16 24 48 72
    32 48 96 144
Facoltativo: gestire la matrice con i puntatori evitando la notazione con le parentesi quadre.*/
void carica(int m[R][C])
{
    int i, j;

    for (j = 0; j < C; j++)
    {
        printf("Inserire i valori nella prima riga %d: ", j);
        scanf("%d", &m[0][j]);
    }
    for (i = 1; i < R; i++)
        for (j = 0; j < C; j++)
            m[i][j] = m[i - 1][j] * 2;
}

/*Una funzione che
- riceve in ingresso una matrice di numeri interi.
- Visualizza i valori contenuti nella matrice con i relativi indici, come nell’esempio.
- Non restituisce niente.
Esempio:
    0   1   2   3
    -   -   -   -
0 | 2   3   6   9
1 | 4   6   12  18
2 | 8   12  24  36
3 | 16  24  48  72
4 | 32  48  96  144*/
void visualizza(int m[R][C])
{
    int i, j;

    printf("\t\t");

    for (j = 0; j < C; j++)
        printf("%d\t", j);
    printf("\n");

    printf("\t\t");

    for (j = 0; j < C; j++)
        printf("-\t");
    printf("\n");

    for (i = 0; i < R; i++)
    {
        printf("%d\t|\t", i);
        for (j = 0; j < C; j++)
            printf("%d\t", m[i][j]);
        printf("\n");
    }
}

/*Una funzione che
- riceve in ingresso una matrice di numeri interi e un valore intero.
- Ricerca tale valore nella matrice.
- Restituisce 1 se presente, 0 se assente.*/
int cerca(int m[R][C], int n)
{
    int i, j, esito;
    esito = 0;

    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
            if (m[i][j] == n)
                esito = 1;
    }
    return esito;
}

/*Una funzione che
- riceve in ingresso una matrice di numeri interi e l’indice di una colonna.
- Se l’indice della colonna è compatibile con le dimensioni della matrice, restituisce la
    somma dei valori su tale colonna.
- Se l’indice non è compatibile restituisce -1.
Esempio: indice colonna: 1 ---> somma: 93*/
int somma(int m[R][C], int x)
{
    int i, j, s;

    if (x < 0 || x >= C)
    {
        s = -1;
    }

    else
    {
        s = 0;
        for (i = 0; i < R; i++)
        {
            s = s + m[i][x];
        }
    }
    return s;
}
