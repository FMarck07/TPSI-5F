#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct {
    char nome[MAX];
    char cognome[MAX];
    int eta;
    char codice_fiscale[16];
    float reddito_annuo; 
    int anno_nascita;
    char residenza[MAX];
} Persona;

void InserisciPersona(Persona p[], int *n){
    printf("Inserisci il numero di persone da inserire: ");
    scanf("%d", n);
    for(int i = 0; i < *n; i++){
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

void Visualizza(Persona p){
    printf("Nome: %s, Cognome: %s, Eta: %d, Codice fiscale: %s, Reddito: %.2f, Anno nascita: %d, Residenza: %s\n", 
           p.nome, p.cognome, p.eta, p.codice_fiscale, p.reddito_annuo, p.anno_nascita, p.residenza);
}

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

void CercaCodiceFiscale(Persona elenco[], int n, char cf[]){
    for(int i = 0; i < n; i++){
        if(strcmp(elenco[i].codice_fiscale, cf) == 0){
            Visualizza(elenco[i]);
            return;
        }
    }
    printf("Persona non trovata.\n");
}

/**
 * @brief Visualizza tutte le persone con reddito >= valore specificato.
 * @return 1 se trovate, 0 se nessuna trovata.
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
 * @brief Calcola e stampa la media dei redditi delle persone.
 */
void MediaReddito(Persona elenco[], int n){
    if(n == 0){
        printf("Nessuna persona registrata.\n");
        return;
    }
    float somma = 0;
    for(int i = 0; i < n; i++){
        somma += elenco[i].reddito_annuo;
    }
    printf("Media reddito: %.2f\n", somma / n);
}

/**
 * @brief Visualizza tutte le persone nate in un anno specifico.
 * @return 1 se trovate, 0 se nessuna trovata.
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

int main(){
    int n, scelta, anno;
    char cf[16];
    float reddito;
    Persona elenco[MAX];

    InserisciPersona(elenco, &n);

    do{
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
                CercaCodiceFiscale(elenco, n, cf);
                break;
            case 4:
                printf("Inserisci un reddito minimo: ");
                scanf("%f", &reddito);
                if(VisualizzaRedditoSuperiore(elenco, n, reddito) == 0)
                    printf("Nessuna persona con reddito >= %.2f trovata.\n", reddito);
                break;
            case 5:
                MediaReddito(elenco, n);
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

    return 0;
}
