/*
Esercizio 2
Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input 1 stringa
e un carattere, e dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al Client il
numero di occorrenze del carattere nella stringa.
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

#define DIM 50
#define SERVERPORT 1313

int main(int argc, char** argv)
{
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    char str1[DIM];
    char carattere;
    int socketfd;
    int occorrenze;

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

    printf("Inserisci il carattere da cercare: ");
    scanf(" %c", &carattere);  // lo spazio prima di %c serve per ignorare newline

    write(socketfd, str1, sizeof(str1));
    write(socketfd, &carattere, sizeof(carattere));

    read(socketfd, &occorrenze, sizeof(occorrenze));

    printf("Il carattere '%c' compare %d volte nella stringa \"%s\".\n", carattere, occorrenze, str1);

    close(socketfd);
    return 0;
}
