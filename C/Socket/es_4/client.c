/*
Esercizio 4
Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input 1 stringa
e, dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al Client 2 stringhe&gt; la
prima composta dalle lettere di posizione pari e la seconda composta dalle lettere di posizione dispari.
*/

// CLIENT
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 100
#define SERVERPORT 1313

int main(int argc, char** argv)
{
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    char str1[DIM];
    char pari[DIM];
    char dispari[DIM];
    int socketfd;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Errore creazione socket");
        exit(1);
    }

    if (connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) < 0) {
        perror("Errore connessione al server");
        close(socketfd);
        exit(1);
    }

    printf("Inserisci la stringa: ");
    scanf("%s", str1);

    write(socketfd, str1, sizeof(str1));

    read(socketfd, pari, sizeof(pari));
    read(socketfd, dispari, sizeof(dispari));

    printf("Caratteri in posizione pari: %s\n", pari);
    printf("Caratteri in posizione dispari: %s\n", dispari);

    close(socketfd);
    return 0;
}
