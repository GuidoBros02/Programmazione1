#include<stdio.h>
#define DIM 30

void carica(int v[], char file[]);
void visualizza(int v[]);
int minimo(int v[]);
void copia(int*v1, int*v2);

/*La funzione main che
• riceve in ingresso il nome di un file da riga di comando.
• Dichiara due vettori di interi, ciascuno di dimensione 30.
• Invoca la prima funzione per caricare il primo vettore da file.
• Invoca la seconda funzione per visualizzare il contenuto del primo vettore.
• Invoca la terza funzione per il calcolo del minimo del primo vettore. Ne visualizza il
risultato tramite un opportuno messaggio.
• Invoca la quarta funzione per la copia parziale del primo vettore nel secondo.
• Invoca di nuovo la seconda funzione per visualizzare il contenuto del secondo
vettore.
• Invoca di nuovo la terza funzione per il calcolo del minimo del secondo vettore. Ne
visualizza il risultato tramite un opportuno messaggio*/
int main (int argc, char*argv[])
{
    if(argc!=2)
    {
        printf("Numero di argomenti errato, inserire nome del file\n");
        return 1;
    }
    else
    {
        int vet1[DIM], vet2[DIM], min, min2;
        
        carica(vet1,argv[1]);
        visualizza(vet1);
        min=minimo(vet1);
        printf("Il numero minimo nel primo vettore e' pari a %d\n\n", min);
        copia(vet1,vet2);
        visualizza(vet2);
        min2=minimo(vet2);
        printf("Il numero minimo nel secondo vettore e' pari a %d\n\n", min2);
        
        return 0;
    }

}

/*Una funzione che
- riceve in ingresso un vettore di numeri interi e il nome di un file.
- Apre il file.
. Carica nel vettore i numeri contenuti nel file (si assume che il file contenga valori
    interi e positivi, la cui quantità è inferiore alla dimensione del vettore).
- Mette il valore -1 come “tappo” del vettore.
- Chiude il file.
- Non restituisce niente.*/
void carica(int v[], char file[])
{
    int i;
    i=0; 
    FILE*fp;

    fp=fopen(file, "r");

    if(fp==NULL)
    {
        printf("Errore nell'apertura del file\n");
    }
    else
    {
        while(fscanf(fp, "%d", &v[i])!=EOF)
        i++;

        v[i]=-1;
        fclose(fp);
    }
}

/*Una funzione che
- riceve in ingresso un vettore di numeri interi con -1 come “tappo”.
- Visualizza il contenuto del vettore seguendo la notazione indice: valore escludendo il
    “tappo”. Esempio: 0: 22 1: 7 2: 10 3: 5 4:15 5: 8 ...
- Non restituisce niente*/
void visualizza(int v[])
{
    int i;

    for(i=0; v[i]!=-1; i++)
    {
        printf("%d: %d\t", i, v[i]);
    }
    printf("\n\n");
}

/*Una funzione che
- riceve in ingresso un vettore di numeri interi con -1 come “tappo”.
- Calcola il valore minimo all’interno del vettore (il “tappo” non viene considerato nel
    calcolo). Esempio: 22 7 10 5 15 8 ---> minimo: 5
- Restituisce il valore minimo.*/
int minimo(int v[])
{
    int i, m;
    m=v[0];

    for(i=1; v[i]!=-1; i++)
    {
        if(v[i]<m)
            m=v[i];
    }
    return m;
}

/*Una funzione che
• riceve in ingresso due vettori di interi (v1, v2).
• Copia in v2 i valori di v1 composti da due cifre.
    Esempio: v1: 22 7 10 5 15 8 ---> v2: 22 10 15
• Mette il valore -1 come “tappo” di v2.
• Non restituisce niente.
• Facoltativo: gestire i vettori tramite i puntatori e la loro aritmetica.*/
void copia(int *v1, int *v2)
{
    int i, k=0;
    
    for (i=0; *(v1+i)!=-1; i++)
        if (*(v1+i)>=10 && *(v1+i)<100)
        {
            *(v2+k)=*(v1+i);
            k++;
        }
        
    *(v2+k)=-1;
}
