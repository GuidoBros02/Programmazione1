#include <stdio.h>
#include <string.h>
#define DIM 30

void carica(char s[]);
int conta(char s[]);
void copia(char s1[], char s2[]);
void sposta(char s[]);

/*La funzione main che
• si aspetta in ingresso il nome di un file (da riga di comando).
• Se il nome del file non viene passato, visualizza un opportuno messaggio di errore.
• Se il nome viene passato, ma non esiste un file con quel nome, allora visualizza un
    opportuno messaggio di errore.
• Se il file esiste, tenta di caricare una singola stringa da file; se il file è vuoto,
    visualizza un opportuno messaggio di errore, altrimenti esegue le seguenti operazioni:
• invoca la funzione per visualizzare la stringa.
• Invoca la funzione per la quantità di cifre nella stringa; quindi ne visualizza il
    risultato traminte un opportuno messaggio.
• Invoca la funzione per la copia parziale della stringa in una seconda stringa;
    quindi invoca la funzione di visualizzazione applicata alla seconda stringa.
• Invoca la funzione di shift applicata alla prima stringa; quindi invoca la
    funzione di visualizzazione applicata alla prima stringa. */
int main(int argc, char*argv[])
{
    if(argc!=2)
    {
        printf("Errore nella compilaizone.\n");
    }
    else
    {
        FILE*fp; 
        char str1[DIM], str2[DIM];
        int cer; 

        fp=fopen(argv[1], "r");

        if(fp==NULL)
        {
            printf("Non esiste file con questo nome.\n");
        }
        else
        {
            if (fscanf(fp, "%s", str1) == EOF)
            {
                printf("Il file è vuoto.\n");
            }
            else
            {
                carica(str1);
                cer=conta(str1);
                printf("N cifre: %d", cer);
                copia(str1, str2);
                carica(str2);
                sposta(str1);
                carica(str1);
            }
        }
    }
    return 0;
}

/*Una funzione che
• riceve in ingresso una stringa.
• Visualizza sullo schermo la stringa, circondata da una cornice composta dal carattere #
(la lunghezza della cornice deve essere proporzionata alla lunghezza della stringa).
• Non restituisce niente.
• Esempio
stringa MICROsoft,WINdows,8.1? ---> ############################
                                    #  MICROsoft,WINdows,8.1?  #
                                    ############################ */
void carica(char s[])
{
    int i, l; 
    l=(int)strlen(s);

    printf("\n");
    for(i=0; i<l+6; i++)
    {
        printf("#");
    }
    printf("\n#  %s  #\n", s);

    for(i=0; i<l+6; i++)
    {
        printf("#");
    }
    printf("\n\n");
}

/*Una funzione che
• riceve in ingresso una stringa.
• Restituisce la quantità di cifre (0, 1, 2, ..., 9) presenti nella stringa.
• Esempio stringa MICROsoft,WINdows,8.1? ---> 2 cifre */
int conta(char s[])
{
    int i, c, l; 
    c=0; 
    l=(int)strlen(s);

    for(i=0; i<l; i++)
    {
        if(s[i]>='0' && s[i]<='9')
            c++;
    }
    return c;
}

/*Una funzione che
• riceve in ingresso due stringhe (s1, s2).
• Copia in s2 le cifre presenti in s1.
• Non restituisce niente.
• Esempio s1 MICROsoft,WINdows,8.1? ---> s2 81
• Facoltativo: gestire le stringhe con i puntatori, evitando la notazione con le parentesi
    quadre. */
void copia(char s1[], char s2[])
{
    int i, l, j;
    l=(int)strlen(s1);
    j=0; 
    for(i=0; i<l; i++)
    {
        if(s1[i] >='0' && s1[i] <='9')
        {
            s2[j]=s1[i];
            j++;
        }
    }
    s2[j]='\0';
}
/*
void copia_cifre_fac(char *s1, char *s2)
{
    int i, j, l;

    l = 0;
    while (*(s1 + l) != '\0')
        l++;

    j = 0;
    for (i = 0; i < l; i++)
        if (*(s1 + i) >= '0' && *(s1 + i) <= '9')
        {
            *(s2 + j) = *(s1 + i);
            j++;
        }
    *(s2 + j) = '\0';
}
*/

/*Una funzione che
• riceve in ingresso una stringa.
• Esegue sulla stringa lo shift a sinistra non circolare, sostituendo il carattere scartato
con il carattere _
• Non restituisce niente.
• Esempio MICROsoft,WINdows,8.1? ---> ICROsoft,WINdows,8.1?_*/
void sposta(char s[])
{
    int i, l;

    l=(int)strlen(s);

    for(i=0; i<l-1; i++)
    {
        s[i] = s[i + 1];
    }
    s[l-1]='_';
}

