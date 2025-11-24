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

int main() {
    struct sockaddr_in servizio;
    int socketfd;
    int vet[10] = {1, 3, 6, 7, 8, 9, 11, 13, 16, 17};
    char risposta[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("chiamata alla system call socket fallita");
        exit(1);
    }

    if (connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) == -1) {
        printf("chiamata alla system call connect fallita");
        exit(1);
    }

    write(socketfd, vet, sizeof(vet));

    read(socketfd, risposta, sizeof(risposta));

    printf("Risposta del server: %s\n", risposta);

    close(socketfd);
    return 0;
}

