#include <stdio.h>
#include <string.h>
#define DIM 30

void carica(char s[]);
void visualizza(char *s);
void cripta(char s[], char nome[]);
int decripta(char s1[], char nome[]);

/*La funzione main che
• riceve in ingresso un solo parametro cioè il nome di un file. In caso contrario mostra
un opportuno messaggio di errore e termina.
• Dichiara una stringa di dimensione 30.
• Invoca la funzione per impostare la password (stringa).
• Invoca la funzione per visualizzare la password.
• Invoca la funzione per salvare la password su file.
• Chiede all’utente di re-inserire la password.
• Invoca la funzione che confronta la password re-inserita con quella salvata su file.
• Mostra un opportuno messaggio in base all’esito del confronto*/
int main(int argc, char *argv[])
{
    if (argc != 2)
        printf("\nERRORE\n\n");
    else
    {
        char p[DIM];
        int v;
        carica(p);
        visualizza(p);
        cripta(p, argv[1]);
        printf("\nRe-inserire la password: ");
        scanf("%s", p);
        v = decripta(p, argv[1]);
        if (v)
            printf("\nPassword corretta.\n\n");
        else
            printf("\nPassowrd errata.\n\n");
    }
    return 0;
}

/*Una funzione che
- riceve in ingresso una stringa (s).
- Chiede all’utente di inserire una password che viene memorizzata in s.
- La password deve essere composta da almeno 8 caratteri. Tra questi, almeno 3
    devono essere lettere maiuscole.
    Esempi: K1ABuCx. D1c;RC2v ?XbYZU3a
- Finché la password non soddisfa i requisiti mostra un opportuno messaggio di errore
    e ripete la richiesta di inserimento.
- Non restituisce niente.*/
void carica(char s[])
{
    int l, c, i;

    do
    {
        printf("inserire una password contenente almeno 8 caratteri e 3 di questi maiuscoli: ");
        scanf("%s", s);

        l = strlen(s);

        c = 0;
        for (i = 0; i < l; i++)
        {
            if (s[i] >= 'A' && s[i] <= 'Z')
                c++;
        }
    } while (l < 8 || c < 3);
}

/*Una funzione che
- riceve in ingresso una stringa tramite puntatore.
- Visualizza il messaggio “La password inserita e’ ”.
- Utilizzando l’aritmetica dei puntatori visualizza i caratteri nella stringa separati dal
    simbolo - .
- Esempi: K-1-A-B-u-C-x-. D-1-c-;-R-C-2-v ?-X-b-Y-Z-U-3-a
- Non restituisce niente.*/
void visualizza(char *s)
{
    int i, l;
    printf("La password inseririta e': ");
    printf("\n\n");

    l = strlen(s);
    for (i = 0; i < l; i++)
    {
        if (i <= l - 2)
            printf("%c-", *(s + i));
        else
            printf("%c\n", *(s + i));
    }
}

/*Una funzione che
- riceve in ingresso una stringa (s) e il nome di un file.
- Salva s nel file in modo “criptato”: nel file ogni carattere di s viene sostituito dal
    carattere che si trova dopo 3 posizioni nella tabella ASCII (allegata all’esercizio).
    Esempi: s: K1ABuCx. ---> file:N4DExF{1
            s: D1c;RC2v ---> file:G4f>UF5y
            s: ?XbYZU3a ---> file: B[e\]X6d
• Non restituisce niente*/
void cripta(char s[], char nome[])
{
    FILE *fp;
    int i;
    char c;
    fp = fopen(nome, "w");
    for (i = 0; s[i] != '\0'; i++)
    {
        c = s[i] + 3;
        fprintf(fp, "%c", c);
    }
    fclose(fp);
}

/*Una funzione che
• riceve in ingresso una stringa (s1) e il nome di un file.
• Legge da file la stringa “criptata” (s2).
• Restituisce il valore 1 se s1 corrisponde a s2 decriptata; altrimenti restituisce 0.*/
int decripta(char s1[], char nome[])
{
    FILE *fp;
    int i, l1, l2, esito;
    char s2[DIM];
    fp = fopen(nome, "r");
    fscanf(fp, "%s", s2);
    fclose(fp);
    esito = 1;
    l1 = strlen(s1);
    l2 = strlen(s2);
    if (l1 != l2)
        esito = 0;
    else
        for (i = 0; i < l1 && esito == 1; i++)
            if (s1[i] != s2[i] - 3)
                esito = 0;
    return esito;
}