/* 
Scrivere un programma in C che dopo aver dichiarato una struttura denominata Persona con i
seguenti campi: Nome, Cognome, età, codice fiscale, reddito annuo, anno_nascita, residenza(città);
determini:
1) La persona con reddito annuo più alto e quella con reddito annuo più basso.
2) Ordini la lista delle persone in base all’anno di nascita (dal più anziano al più giovane).
3) Consenta all’utente di cercare una persona inserendo il codice fiscale.
4) Visualizzi tutte le persone con reddito superiore o uguale a un valore scelto dall’utente.
5) Calcoli la media dei redditi delle persone registrate nel sistema.
6) Visualizzi tutte le persone nate in un anno specifico, scelto dall’utente.
*/

#include <stdio.h>
#include <string.h>
#define MAX 100 

/**
 * @brief Struttura che rappresenta una persona
 */
typedef struct {
    char nome[MAX];
    char cognome[MAX];
    int eta;
    char codice_fiscale[16];
    float reddito_annuo; 
    int anno_nascita;
    char residenza[MAX];
} Persona;

/**
 * @brief Inserisce i dati di più persone in un array di strutture.
 * @param p Array di persone.
 * @param n Puntatore al numero di persone da inserire.
 */
void InserisciPersona(Persona p[], int *n){
    printf("Quante persone vuoi inserire? ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++){
        printf("\nPersona %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", p[i].nome);
        printf("Cognome: ");
        scanf("%s", p[i].cognome);
        printf("Età: ");
        scanf("%d", &p[i].eta);
        printf("Codice Fiscale: ");
        scanf("%s", p[i].codice_fiscale);
        printf("Reddito annuo: ");
        scanf("%f", &p[i].reddito_annuo);
        printf("Anno nascita: ");
        scanf("%d", &p[i].anno_nascita);
        printf("Città di residenza: ");
        scanf("%s", p[i].residenza);
    }
}

/**
 * @brief Visualizza la persona con il reddito massimo e minimo.
 * @param elenco Array di persone.
 * @param n Numero di persone.
 */
void VisualizzaMINMAX(Persona elenco[], int n){
    int max = 0, min = 0;
    for(int i = 1; i < n; i++){
        if(elenco[i].reddito_annuo > elenco[max].reddito_annuo)
            max = i;
        if(elenco[i].reddito_annuo < elenco[min].reddito_annuo)
            min = i;
    }

    printf("\nPersona con reddito più alto:\n");
    printf("%s %s, %s, %.2f\n", elenco[max].nome, elenco[max].cognome, elenco[max].residenza, elenco[max].reddito_annuo);

    printf("\nPersona con reddito più basso:\n");
    printf("%s %s, %s, %.2f\n", elenco[min].nome, elenco[min].cognome, elenco[min].residenza, elenco[min].reddito_annuo);
}

/**
 * @brief Ordina le persone per anno di nascita (dal più anziano al più giovane).
 * @param elenco Array di persone.
 * @param n Numero di persone.
 */
void OrdinaNascita(Persona elenco[], int n){
    Persona tmp;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(elenco[j].anno_nascita > elenco[j + 1].anno_nascita){
               tmp = elenco[j];  
               elenco[j] = elenco[j + 1];
               elenco[j + 1] = tmp;
            }
        }
    }

    printf("\nElenco ordinato per anno di nascita:\n");
    for(int i = 0; i < n; i++){
        printf("%s %s, Anno: %d\n", elenco[i].nome, elenco[i].cognome, elenco[i].anno_nascita);
    }
}

/**
 * @brief Cerca una persona tramite codice fiscale.
 * @param elenco Array di persone.
 * @param n Numero di persone.
 * @param cf Codice fiscale da cercare.
 */
void CercaCodiceFiscale(Persona elenco[], int n, char cf[16]){
    int trovato = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(cf, elenco[i].codice_fiscale) == 0){
            printf("\nPersona trovata:\n%s %s, CF: %s\n", elenco[i].nome, elenco[i].cognome, elenco[i].codice_fiscale);
            trovato = 1;
        }
    }
    if(!trovato)
        printf("\nCodice fiscale non trovato.\n");
}

/**
 * @brief Visualizza persone con reddito superiore o uguale a una soglia.
 * @param elenco Array di persone.
 * @param n Numero di persone.
 * @param reddito Reddito minimo scelto.
 */
void VisualizzaRedditoSuperiore(Persona elenco[], int n, float reddito){
    printf("\nPersone con reddito >= %.2f:\n", reddito);
    for(int i = 0; i < n; i++){
        if(elenco[i].reddito_annuo >= reddito){
            printf("%s %s, %.2f\n", elenco[i].nome, elenco[i].cognome, elenco[i].reddito_annuo);
        }
    }
}

/**
 * @brief Calcola e visualizza la media dei redditi.
 * @param elenco Array di persone.
 * @param n Numero di persone.
 */
void VisualizzaMediaReddito(Persona elenco[], int n){
    float somma = 0;
    for(int i = 0; i < n; i++)
        somma += elenco[i].reddito_annuo;
    printf("\nMedia dei redditi: %.2f\n", somma / n);
}

/**
 * @brief Visualizza persone nate in un anno specifico.
 * @param elenco Array di persone.
 * @param n Numero di persone.
 * @param anno Anno di nascita da cercare.
 */
void VisualizzaPersoneAnno(Persona elenco[], int n, int anno){
    printf("\nPersone nate nell'anno %d:\n", anno);
    for(int i = 0; i < n; i++){
        if(elenco[i].anno_nascita == anno){
            printf("%s %s, %d\n", elenco[i].nome, elenco[i].cognome, elenco[i].anno_nascita);
        }
    }
}

/**
 * @brief Funzione principale con menù e gestione tramite switch-case.
 */
int main(){
    Persona elenco[MAX];
    int n = 0, scelta, anno;
    char cf[16];
    float reddito;

    InserisciPersona(elenco, &n);

    do {
        printf("\n===== MENU =====\n");
        printf("1. Visualizza reddito massimo e minimo\n");
        printf("2. Ordina per anno di nascita\n");
        printf("3. Cerca persona per codice fiscale\n");
        printf("4. Visualizza persone con reddito >= valore scelto\n");
        printf("5. Calcola media redditi\n");
        printf("6. Visualizza persone nate in un anno specifico\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                VisualizzaMINMAX(elenco, n);
                break;
            case 2:
                OrdinaNascita(elenco, n);
                break;
            case 3:
                printf("Inserisci codice fiscale: ");
                scanf("%s", cf);
                CercaCodiceFiscale(elenco, n, cf);
                break;
            case 4:
                printf("Inserisci reddito minimo: ");
                scanf("%f", &reddito);
                VisualizzaRedditoSuperiore(elenco, n, reddito);
                break;
            case 5:
                VisualizzaMediaReddito(elenco, n);
                break;
            case 6:
                printf("Inserisci anno di nascita: ");
                scanf("%d", &anno);
                VisualizzaPersoneAnno(elenco, n, anno);
                break;
            case 0:
                printf("Uscita dal programma...\n");
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while (scelta != 0);

    return 0;
}
