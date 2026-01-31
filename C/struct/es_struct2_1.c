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

/**
 * @brief Inserisce le persone nel sistema (può usare printf e scanf)
 * @param p Array di persone.
 * @param n Puntatore al numero di persone.
 */
void InserisciPersona(Persona p[], int *n) {
    printf("Inserisci il numero di persone da inserire: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
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
 * @brief Visualizza le informazioni di una persona (può usare printf)
 */
void Visualizza(Persona p) {
    printf("Nome: %s, Cognome: %s, Eta: %d, Codice fiscale: %s, Reddito: %.2f, Anno nascita: %d, Residenza: %s\n",
           p.nome, p.cognome, p.eta, p.codice_fiscale, p.reddito_annuo, p.anno_nascita, p.residenza);
}

/**
 * @brief Trova gli indici del reddito minimo e massimo (no printf)
 */
void TrovaRedditoMinMax(Persona p[], int n, int *min, int *max) {
    *min = 0;
    *max = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].reddito_annuo > p[*max].reddito_annuo)
            *max = i;
        if (p[i].reddito_annuo < p[*min].reddito_annuo)
            *min = i;
    }
}

/**
 * @brief Ordina le persone per anno di nascita (no printf)
 */
void Ordinamento(Persona elenco[], int n) {
    Persona tmp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (elenco[j].anno_nascita > elenco[j + 1].anno_nascita) {
                tmp = elenco[j];
                elenco[j] = elenco[j + 1];
                elenco[j + 1] = tmp;
            }
        }
    }
}

/**
 * @brief Cerca una persona tramite codice fiscale (no printf)
 */
int CercaCodiceFiscale(Persona elenco[], int n, char cf[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(elenco[i].codice_fiscale, cf) == 0)
            return i;
    }
    return -1;
}

/**
 * @brief Filtra persone con reddito >= valore (no printf)
 */
int FiltraRedditoSuperiore(Persona elenco[], int n, float reddito, Persona risultato[]) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (elenco[i].reddito_annuo >= reddito) {
            risultato[k++] = elenco[i];
        }
    }
    return k;
}

/**
 * @brief Calcola la media dei redditi (no printf)
 */
float MediaReddito(Persona elenco[], int n) {
    if (n == 0)
        return 0;
    float somma = 0;
    for (int i = 0; i < n; i++)
        somma += elenco[i].reddito_annuo;
    return somma / n;
}

/**
 * @brief Filtra persone nate in un anno specifico (no printf)
 */
int FiltraAnno(Persona elenco[], int n, int anno, Persona risultato[]) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (elenco[i].anno_nascita == anno)
            risultato[k++] = elenco[i];
    }
    return k;
}

int main() {
    Persona elenco[MAX], risultato[MAX];
    int n, scelta, anno, min, max;
    float reddito;
    char cf[16];

    InserisciPersona(elenco, &n);

    do {
        printf("\nMenu\n");
        printf("0. Esci dal programma\n");
        printf("1. Reddito più alto e più basso\n");
        printf("2. Ordinamento per anno di nascita\n");
        printf("3. Cerca per codice fiscale\n");
        printf("4. Persone con reddito superiore a un valore\n");
        printf("5. Media reddito\n");
        printf("6. Persone nate in un anno specifico\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                TrovaRedditoMinMax(elenco, n, &min, &max);
                printf("\nPersona con reddito massimo:\n");
                Visualizza(elenco[max]);
                printf("\nPersona con reddito minimo:\n");
                Visualizza(elenco[min]);
                break;

            case 2:
                Ordinamento(elenco, n);
                for (int i = 0; i < n; i++)
                    Visualizza(elenco[i]);
                break;

            case 3:
                printf("Inserisci codice fiscale da cercare: ");
                scanf("%s", cf);
                {
                    int idx = CercaCodiceFiscale(elenco, n, cf);
                    if (idx != -1)
                        Visualizza(elenco[idx]);
                    else
                        printf("Persona non trovata.\n");
                }
                break;

            case 4:
                printf("Inserisci valore minimo di reddito: ");
                scanf("%f", &reddito);
                {
                    int trovati = FiltraRedditoSuperiore(elenco, n, reddito, risultato);
                    if (trovati == 0)
                        printf("Nessuna persona trovata.\n");
                    else
                        for (int i = 0; i < trovati; i++)
                            Visualizza(risultato[i]);
                }
                break;

            case 5:
                printf("Media reddito: %.2f\n", MediaReddito(elenco, n));
                break;

            case 6:
                printf("Inserisci anno: ");
                scanf("%d", &anno);
                {
                    int trovati = FiltraAnno(elenco, n, anno, risultato);
                    if (trovati == 0)
                        printf("Nessuna persona trovata.\n");
                    else
                        for (int i = 0; i < trovati; i++)
                            Visualizza(risultato[i]);
                }
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
