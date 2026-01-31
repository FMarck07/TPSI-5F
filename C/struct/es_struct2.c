#include <stdio.h>
#include <string.h>
#define MAX 100

/**
 * @struct Persona
 * @brief Rappresenta le informazioni di una persona.
 * 
 * Contiene nome, cognome, età, codice fiscale, reddito annuo, anno di nascita e città di residenza.
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
 * @brief Inserisce una serie di persone in un array.
 * @param p Array di persone da popolare.
 * @param n Numero di persone da inserire.
 */
void InserisciPersona(Persona p[], int n){
    for(int i = 0; i < n; i++){
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
 * @brief Stampa le informazioni di una singola persona.
 * @param p Persona da visualizzare.
 */
void Visualizza(Persona p){
    printf("Nome: %s, Cognome: %s, Eta: %d, Codice fiscale: %s, Reddito: %.2f, Anno nascita: %d, Residenza: %s\n", 
           p.nome, p.cognome, p.eta, p.codice_fiscale, p.reddito_annuo, p.anno_nascita, p.residenza);
}

/**
 * @brief Trova e visualizza le persone con reddito massimo e minimo.
 * @param p Array di persone.
 * @param n Numero di persone nell'array.
 */
void VisualizzaRedditoMinMax(Persona p[], int n){
    int min = 0, max = 0;
    for(int i = 1; i < n; i++){
        if(p[i].reddito_annuo > p[max].reddito_annuo){
            max = i;
        }
        if(p[i].reddito_annuo < p[min].reddito_annuo){
            min = i;
        }
    }
    printf("\nPersona con reddito massimo:\n");
    Visualizza(p[max]);
    printf("\nPersona con reddito minimo:\n");
    Visualizza(p[min]);
}

/**
 * @brief Ordina le persone in base all'anno di nascita (dal più vecchio al più giovane) e le visualizza.
 * @param elenco Array di persone.
 * @param n Numero di persone nell'array.
 */
void Ordinamento(Persona elenco[], int n){
    Persona tmp;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(elenco[j].anno_nascita > elenco[j+1].anno_nascita){
                tmp = elenco[j];
                elenco[j] = elenco[j+1];
                elenco[j+1] = tmp;
            }
        }
    }
    for(int i = 0; i < n; i++){
        Visualizza(elenco[i]);
    }
}

/**
 * @brief Cerca una persona tramite codice fiscale.
 * @param elenco Array di persone.
 * @param n Numero di persone nell'array.
 * @param cf Codice fiscale da cercare.
 * @return 1 se la persona è stata trovata, 0 altrimenti.
 */
int CercaCodiceFiscale(Persona elenco[], int n, char cf[]){
    for(int i = 0; i < n; i++){
        if(strcmp(elenco[i].codice_fiscale, cf) == 0){
            Visualizza(elenco[i]);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Visualizza tutte le persone con reddito superiore o uguale a un valore specificato.
 * @param elenco Array di persone.
 * @param n Numero di persone nell'array.
 * @param reddito Valore minimo del reddito da filtrare.
 * @return 1 se almeno una persona soddisfa la condizione, 0 altrimenti.
 */
int VisualizzaRedditoSuperiore(Persona elenco[], int n, float reddito){
    int trovato = 0;
    for(int i = 0; i < n; i++){
        if(elenco[i].reddito_annuo >= reddito){
            Visualizza(elenco[i]);
            trovato = 1;
        }
    }
    return trovato;
}

/**
 * @brief Calcola la media dei redditi delle persone.
 * @param elenco Array di persone.
 * @param n Numero di persone nell'array.
 * @return Media dei redditi; 0 se l'array è vuoto.
 */
float MediaReddito(Persona elenco[], int n){
    if(n == 0) return 0;
    float somma = 0;
    for(int i = 0; i < n; i++){
        somma += elenco[i].reddito_annuo;
    }
    return somma / n;
}

/**
 * @brief Visualizza tutte le persone nate in un anno specifico.
 * @param elenco Array di persone.
 * @param n Numero di persone nell'array.
 * @param anno Anno di nascita da cercare.
 * @return 1 se almeno una persona è stata trovata, 0 altrimenti.
 */
int VisualizzaAnno(Persona elenco[], int n, int anno){
    int trovato = 0;
    for(int i = 0; i < n; i++){
        if(anno == elenco[i].anno_nascita){
            Visualizza(elenco[i]);
            trovato = 1;
        }
    }
    return trovato;
}

/**
 * @brief Funzione principale del programma.
 * Permette di inserire persone e interagire tramite un menu per effettuare diverse operazioni.
 */
int main(){
    int n, scelta, anno;
    char cf[16];
    float reddito;
    Persona elenco[MAX];

    // Richiesta del numero di persone da inserire
    printf("Inserisci il numero di persone da inserire: ");
    scanf("%d", &n);

    if(n > 0){
        // Inserimento iniziale delle persone
        InserisciPersona(elenco, n);

        do{
            // Visualizzazione menu
            printf("\nMenu\n");
            printf("0. Esci dal programma\n");
            printf("1. Reddito + alto e + basso\n");
            printf("2. Ordinamento\n");
            printf("3. Cerca per codice fiscale\n");
            printf("4. Cerca per reddito superiore\n");
            printf("5. Media reddito\n");
            printf("6. Visualizza persone nate in un anno specifico\n");
            printf("Scelta: ");
            scanf("%d", &scelta);
    
            switch(scelta){
                case 1:
                    VisualizzaRedditoMinMax(elenco, n);
                    break;
                case 2:
                    Ordinamento(elenco, n);
                    break;
                case 3:
                    printf("Inserisci un codice fiscale da cercare: ");
                    scanf("%s", cf);
                    if(CercaCodiceFiscale(elenco, n, cf) == 0)
                        printf("Persona non trovata.\n");
                    break;
                case 4:
                    printf("Inserisci un reddito minimo: ");
                    scanf("%f", &reddito);
                    if(VisualizzaRedditoSuperiore(elenco, n, reddito) == 0)
                        printf("Nessuna persona con reddito >= %.2f trovata.\n", reddito);
                    break;
                case 5:
                    printf("Media reddito: %.2f\n", MediaReddito(elenco, n));
                    break;
                case 6:
                    printf("Inserisci un anno: ");
                    scanf("%d", &anno);
                    if(VisualizzaAnno(elenco, n, anno) == 0)
                        printf("Persona non trovata.\n");
                    break;
                case 0:
                    printf("Uscita dal programma...\n");
                    break;
                default:
                    printf("Scelta non valida!\n");
            }
        } while(scelta != 0);
    } else {
        printf("Nessuna persona inserita\n");
    }

    return 0;
}
