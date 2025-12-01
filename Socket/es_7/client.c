// CLIENT
#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <string.h>     //funz. stringhe
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX
#define DIM 50
#define SERVERPORT 1450

int main(int argc, char **argv){
    struct sockaddr_in servizio;
    char stringa[20];
    int socketfd, fromlen = sizeof(servizio);
    // assegnazione valori alla struttura servizio (dominio, indirizzo, porta)
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    // controllo system call socket
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Chiamata fallita alla system call socket");
        exit(0);
    }
    // controllo system call bind
    if((connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio))) == -1){
        printf("Chiamata fallita alla system call connect");
        exit(0);
    }
    printf("Inserisci una stringa ");
    scanf("%s", stringa);
    // invio stringa al server
    write(socketfd, stringa, strlen(stringa) + 1);
    // ricevo
    read(socketfd, stringa, sizeof(stringa));
    printf("Stringa ricevuta %s\n", stringa);
    close(socketfd);
    return 0;
}
