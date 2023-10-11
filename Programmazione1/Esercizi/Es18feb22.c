#include<stdio.h>

int carica(int dim, int m[dim][dim], char nome[]);
void visualizza(int dim, int m[dim][dim]);
void calcola(int dim, int m[dim][dim], int r, int*p1, int*p2); 
void scambia(int dim, int m[dim][dim]);

/*La funzione main che
• deve ricevere in ingresso (da riga di comando) un solo parametro, cioè il nome di un file. In
caso contrario, mostra un opportuno messaggio di errore e termina.
Esempio: esercizio.out valori.txt
• Chiede all’utente la dimensione e dichiara una matrice quadrata di tale dimensione.
• Invoca la funzione per caricare la matrice passando il nome di file ricevuto in ingresso. Se la
matrice non è stata caricata allora visualizza un opportuno messaggio di errore e termina.
• Invoca la funzione per visualizzare la matrice.
• Chiede all’utente di inserire l’indice di una riga. Invoca la funzione per il calcolo di minimo e
massimo. Visualizza i risultati oppure un opportuno messaggio di errore.
• Invoca la funzione per lo scambio delle colonne. Quindi invoca di nuovo la funzione per
visualizzare la matrice aggiornata*/
int main(int argc, char*argv[])
{
    int d, mat[d][d], e, riga, min, max;


    if(argc!=2)
    {
        printf("Errore, Il programma deve ricevere il nome del file.\n");
    }
    else
    {
        printf("\nInserire la dimensione della matrice: ");
        scanf("%d", &d);

        e=carica(d, mat, argv[1]);
        if(!e)
        {
            printf("\nErrore: il file non esiste.\n");
        }

        else
        {
            visualizza(d, mat);
            printf("Inserire l'indice di una riga: ");
            scanf("%d", &riga);
            calcola(d, mat, riga, &min, &max);

            if(min!=-1 && max!=-1)
            {
                printf("Sulla riga %d il minimo è %d ed il massimo è %d\n", riga, min, max);
            }
            else
            {
                printf("Errore: la riga %d non è presente nella matrice.\n", riga);
            }
            scambia(d, mat);
            visualizza(d, mat);
        }
    }
    return 1;
}

/*Una funzione che
• riceve in ingresso una matrice quadrata di tipo intero, la sua dimensione, il nome di un file.
• Tenta di aprire il file con quel nome.
• Se il file esiste allora copia nella matrice i numeri positivi e pari presenti nel file fino a
riempire completamente la matrice. Quindi chiude il file.
• Esempio:  file: 30 3 52 1 7 14 2 33 76 -2 98 4 -4 2 8 9 25 -10 88 ...
            dimensione: 3
            matrice:    30 52 14
                        2 76 98
                        4 2 8
• Restituisce 1 se la matrice è stata caricata. Altrimenti restituisce 0.*/
int carica(int dim, int m[dim][dim], char nome[])
{
    int i, j, val, esito;
    
    FILE*fp;
    fp=fopen(nome, "r");

    if(fp==NULL)
        esito=0; 

    else
    {
        i=0; 
        j=0; 

        while(fscanf(fp, "%d", &val)!=EOF && i<dim)
            if(val>0 && val%2==0)
            {
                m[i][j]=val;
                j++;

                if(j==dim)
                {
                    j=0; 
                    i++;
                }
            }
        fclose(fp);

        if(i==dim)
            esito=1;
        else
            esito=0; 
    }
}

/*Una funzione che
• riceve in ingresso una matrice quadrata di tipo intero e la sua dimensione.
• Visualizza indici e valori della matrice in forma tabulata. In particolare visualizza in alto gli
indici di colonna e a sinistra gli indici di riga, come nell’esempio.
• Esempio:  0   1   2
            _   _   _
    0 |     30  52  14
    1 |     2   76  98
    2 |     4   2   8
• Non restituisce niente.*/
void visualizza(int dim, int m[dim][dim])
{
    int i, j;

    printf("\n\t\t");

    for(j=0; j<dim; j++)
        printf("%d\t", j);
    printf("\n\t\t");

    for(j=0; j<dim; j++)
        printf("-\t");
    printf("\n");


    for(i=0; i<dim; i++)
    {
        printf("%d\t|\t", i);

        for(j=0; j<dim; j++)
            printf("%d\t", m[i][j]);
        printf("\n");
    }

    printf("\n");
}

/*Una funzione che
• riceve in ingresso una matrice quadrata (m) di tipo intero, la sua dimensione (dim), un
indice di riga (r), due parametri (p1, p2).
• Se r è compatibile con dim allora
◦ calcola e memorizza in p1 il valore minimo presente sulla riga di m con indice r;
◦ calcola e memorizza in p2 il valore massimo presente sulla riga di m con indice r.
• Esempio:  30 52 14
            2 76 98
            4 2 8  
                    r: 0 ---> p1: 14 p2: 52
• Se r non è compatibile con dim allora memorizza -1 sia in p1 sia in p2.
• Non restituisce niente.*/
void calcola(int dim, int m[dim][dim], int r, int*p1, int*p2)
{
    int j;

    if(r>=0 && r<dim)
    {
        *p1=m[r][0];
        *p2=m[r][0];

        for(j=1; j<dim; j++)
        {
            if(m[r][j]<*p1)
                *p1=m[r][j];
            if(m[r][j]>*p2)
                *p2=m[r][j];
        }
    }
    else
    {
        *p1=-1;
        *p2=-1;
    }
}

/*Una funzione che
• riceve in ingresso una matrice quadrata di tipo intero e la sua dimensione.
• Scambia il contenuto della prima colonna con il contenuto dell’ultima colonna.
• Esempio:  30  52  14            14  52  30
            2   76  98     --->   98  76   2
            4   2   8              8   2   4
• Non restituisce niente.*/
void scambia(int dim, int m[dim][dim])
{
    int i, k;

    for(i=0; i<dim; i++)
    {
        k=m[i][0];
        m[i][0]=m[i][dim-1];
        m[i][dim-1]=k;
    }
}