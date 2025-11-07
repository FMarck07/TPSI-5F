/*
Esercizio 2
Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input 1 stringa
e un carattere, e dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al Client il
numero di occorrenze del carattere nella stringa.
*/

// SERVER
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 50
#define SERVERPORT 1313

// Funzione che conta quante volte un carattere appare in una stringa
int conta_occorrenze(char *str, char c) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            count++;
    }
    return count;
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa;
    socklen_t fromlen = sizeof(addr_remoto);
    char str[DIM];
    char carattere;
    int occorrenze;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Errore creazione socket");
        exit(1);
    }

    if (bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) < 0) {
        perror("Errore nel bind");
        close(socketfd);
        exit(1);
    }

    listen(socketfd, 10);

    for (;;) {
        printf("\nServer in ascolto...\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr*)&addr_remoto, &fromlen);
        if (soa < 0) {
            perror("Errore");
        }

        read(soa, str, sizeof(str));
        read(soa, &carattere, sizeof(carattere));

        printf("Stringa ricevuta: %s\n", str);
        printf("Carattere ricevuto: %c\n", carattere);

        occorrenze = conta_occorrenze(str, carattere);

        write(soa, &occorrenze, sizeof(occorrenze));

        printf("Occorrenze inviate al client: %d\n", occorrenze);

        close(soa);
    }

    close(socketfd);
    return 0;
}
