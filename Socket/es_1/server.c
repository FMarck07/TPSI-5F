/*
Esercizio 1
Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input 1 stringa
e, dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al Client il messaggio se
è palindroma oppure non lo è.
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

// Funzione che verifica se una stringa è palindroma
int is_palindrome(char *str) {
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j) {
        if (str[i] != str[j])
            return 0;
        i++;
        j--;
    }
    return 1;
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
    char risposta[DIM];

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
        printf("Stringa ricevuta: %s\n", str);

        if (is_palindrome(str))
            strcpy(risposta, "La stringa e' palindroma");
        else
            strcpy(risposta, "La stringa non e' palindroma");

        write(soa, risposta, sizeof(risposta));

        close(soa);
    }

    close(socketfd);
    return 0;
}
