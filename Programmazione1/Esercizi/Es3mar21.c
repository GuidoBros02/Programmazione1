#include<stdio.h>
#include<string.h>
#define R 30
#define C 20

int carica(char s[R][C], FILE*fp);
void visualizza(char s[R][C], int num);
int occorrenza(char s[R][C], int num, char p[]);
void inserisci(char s[R][C], int *num, char c[]);

/*La funzione main che
• riceve in ingresso il nome di un file da riga di comando. In caso contrario mostra un
opportuno messaggio di errore e termina.
• Apre il file con il nome ricevuto in ingresso. Se il file non esiste mostra un opportuno
messaggio di errore e termina.
• Dichiara un vettore di 30 stringhe, ciascuna di lunghezza massima 20.
• Invoca la funzione per caricare il vettore da file; quindi chiude il file.
• Invoca la funzione per visualizzare il contenuto del vettore.
• Richiede all’utente di inserire una stringa (parola) da cercare nel vettore, invoca la
funzione di ricerca e ne visualizza il risultato tramite un opportuno messaggio.
• Richiede all’utente di inserire una stringa (parola) da inserire nel vettore, invoca la
funzione di inserimento e invoca di nuovo la funzione per visualizzare il vettore.*/
int main(int argc, char*argv[])
{
    if(argc!=2)
    {
        printf("errore nella compilazione da terminale\n");
        return 1;
    }
    else
    {
        FILE*fp;
        fp=fopen(argv[1], "r");

        if(fp==NULL)
        {
            printf("Errore. Il nome del file non esiste\n");
            return 1;
        }
        else
        {
            char stringhe[R][C];
            char cerca[C];
            char ins[C];
            int q, ris;
            q=carica(stringhe, fp);
            fclose(fp);

            visualizza(stringhe, q);
            printf("\ninserire una parola da cercare: ");
            scanf("%s", cerca);
            ris=occorrenza(stringhe, q, cerca);

            if(ris==-1)
            {
                printf("La stringa '%s' non e' presente\n", cerca);
            }
            else
            {
                printf("la stringa '%s' e' presente all'indice %d\n", cerca, ris);
            }
            printf("Inserire una stringa da aggiungere: ");
            scanf("%s", ins);
            inserisci(stringhe, &q, ins);
            visualizza(stringhe, q);

            return 0;
        }
    }
}

/*Una funzione che
- riceve in ingresso un vettore di stringhe e un puntatore a file.
- Carica nel vettore le stringhe (parole) presenti nel file che iniziano per vocale e sono
    composte da almeno 4 caratteri (si assume che il file contenga una quantità di stringhe
    inferiore alla dimensione del vettore).
- Restituisce la quantità di stringhe caricate nel vettore.*/
int carica(char s[R][C], FILE*fp)
{
    int conta=0; 
    char parola[C];

    while (fscanf(fp, "%s", parola)!=EOF)
    {
        if(strlen(parola)>=4 && (parola[0]=='a' || parola[0]=='e' 
            || parola[0]=='i' || parola[0]=='o'
            || parola[0]=='u' || parola[0]=='A' || parola[0]=='E' 
            || parola[0]=='O' || parola[0]=='I' || parola[0]=='U'))
        {
            strcpy(s[conta], parola);
            conta++;
        }
    }
    return conta;
}

/*Una funzione che
- riceve in ingresso un vettore di stringhe e la quantità di stringhe che contiene.
- Visualizza il contenuto del vettore secondo la notazione indice) stringa, con il
carattere – come separatore, e disponendo tutto sulla stessa riga.
- Esempio: 0) echo - 1) aircraft - 2) April – 3) Etna – 4) aircraft – 5) ethics
- Non restituisce niente.*/
void visualizza(char s[R][C], int num)
{
    int i;
    for(i=0; i<num; i++)
    {
        printf("%d) %s", i, s[i]);
        
        if(i<num-1)
        {
            printf(" - ");
        }
        else
        {
            printf("\n\n");
        }
    }
}

/*Una funzione che
- riceve in ingresso un vettore (v) di stringhe, la quantità di stringhe che contiene, e
    una stringa (s).
- Se s è presente nel vettore, restituisce l’indice dell'ultima occorrenza di s.
- Se s è assente, restituisce -1.
- Esempi:   v: echo aircraft April Etna aircraft ethics
            s: aircraft ---> indice: 4
            s: Etna ---> indice: 3
            s: August ---> indice: -1*/
int occorrenza(char s[R][C], int num, char p[])
{
    int i;
    int esito=-1;

    for(i=0; i<num; i++)
    {
        if(strcmp(s[i], p)==0)
        {
            esito=i;
        }
    }
    return esito;
}

/*Una funzione che
• riceve in ingresso un vettore (v) di stringhe, la quantità (q) di stringhe che contiene,
e una stringa (s).
• Inserisce s come quarta stringa del vettore mantenendo tutte le stringhe caricate in
precedenza.
• Esempio:   v: echo aircraft April Etna aircraft ethics s: advance
        ---> v: echo aircraft April advance Etna aircraft ethics
• Aggiorna il valore di q.
• Non restituisce niente.*/
void inserisci(char s[R][C], int *num, char c[])
{
    int i;
    for(i=4; i<(*num)+1; i++)
        strcpy(s[i], s[i-1]);
    strcpy(s[3], c);
    (*num)++;
}
