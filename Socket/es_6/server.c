/*Esercizio 6
Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input un
vettore di numeri e dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al
Client il conteggio dei numeri pari e dei numeri dispari contenuti nel vettore.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define SERVERPORT 1450
#define DIM 100

int contaPari(int vet[]) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (vet[i] % 2 == 0)
            count++;
    }
    return count;
}

int contaDispari(int vet[]) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (vet[i] % 2 != 0)
            count++;
    }
    return count;
}

int main() {
    struct sockaddr_in servizio;
    int socketfd, soa;
    int vet[10], fromlen = sizeof(servizio);
    char risposta[100];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("chiamata alla system call socket fallita");
        exit(1);
    }

    if (bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) == -1) {
        printf("chiamata alla system call bind fallita");
        exit(1);
    }

    if (listen(socketfd, 10) == -1) {
        printf("chiamata alla system call listen fallita");
        exit(1);
    }


    for (;;) {
        printf("Server in ascolto...\n");

        soa = accept(socketfd, (struct sockaddr*)&servizio, &fromlen);
        if (soa == -1) {
            printf("chiamata alla system call accept fallita");
            exit(1);
        }

        read(soa, vet, sizeof(vet));

        int pari = contaPari(vet);
        int dispari = contaDispari(vet);

        snprintf(risposta, sizeof(risposta),"Numeri pari: %d  Numeri dispari: %d",pari, dispari);

        write(soa, risposta, sizeof(risposta));

        close(soa);
    }

    return 0;
}

