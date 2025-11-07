/*
Esercizio 4
Scrivere il codice in C di un'applicazione Socket CLIENT-SERVER in cui il server riceve in input 1 stringa
e, dopo aver effettuato gli opportuni controlli, rispedisce al Client 2 stringhe:
- la prima composta dalle lettere di posizione pari
- la seconda composta dalle lettere di posizione dispari
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM 100
#define SERVERPORT 1313

// Funzione che divide la stringa in due: posizioni pari e dispari
void separa_pari_dispari(char *src, char *pari, char *dispari) {
    int i, p = 0, d = 0;
    for (i = 0; src[i] != '\0'; i++) {
        if (i % 2 == 0)
            pari[p++] = src[i];
        else
            dispari[d++] = src[i];
    }
    pari[p] = '\0';
    dispari[d] = '\0';
}

int main() {
    int socketfd, soa;
    struct sockaddr_in servizio, addr_remoto;
    socklen_t fromlen = sizeof(addr_remoto);
    char str[DIM];
    char pari[DIM], dispari[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Errore creazione socket");
        exit(1);
    }

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    if (bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) < 0) {
        perror("Errore nel bind");
        close(socketfd);
        exit(1);
    }

    listen(socketfd, 10);
    printf("Server avviato. In ascolto sulla porta %d...\n", SERVERPORT);

    for (;;) {
        soa = accept(socketfd, (struct sockaddr*)&addr_remoto, &fromlen);
        if (soa < 0) {
            perror("Errore accept");
            continue;
        }

        read(soa, str, sizeof(str)); // si assume che il client invii la stringa con '\0'

        printf("\nStringa ricevuta: %s\n", str);

        separa_pari_dispari(str, pari, dispari);

        printf("Stringa posizioni pari: %s\n", pari);
        printf("Stringa posizioni dispari: %s\n", dispari);

        write(soa, pari, sizeof(pari));
        write(soa, dispari, sizeof(dispari));

        close(soa);
    }

    close(socketfd);
    return 0;
}
