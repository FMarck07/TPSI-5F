/*Scrivere il codice in C di un’applicazione socket CLIENT–SERVER in cui il server riceve in input una stringa e, dopo aver effettuato gli opportuni controlli (se necessari), rispedisce al client il numero totale di parole presenti nella stringa.
*/

// SERVER
#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <netdb.h>      //strutture hostent e servent che identificano l'host tramite iol nome
#include <string.h>     //funz. stringhe
#include <fcntl.h>      //descrittore di file
#include <signal.h>     //consente l'utilizzo delle funzioni per la gestione dei segnali fra processi
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX
#define SERVERPORT 1450

void parolaSenzaDoppieContinue(char *str) {
    int j = 1;

    for (int i = 1; i < strlen(str); i++) {
        if (str[i] != str[j - 1]) {
            str[j] = str[i];
            j++;
        }
    }

    str[j] = '\0';
}

int main(){
    char stringa[256];
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    int socketfd, soa, froml = sizeof(servizio);
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Chiamata fallita alla system call socket");
        exit(0);
    }
    if(bind(socketfd, (struct sockaddr*) &servizio, froml) == -1){
        printf("Chiamata fallita alla system call bind");
        exit(0);
    }
    if(listen(socketfd, 10) == -1){
        printf("Chiamata fallita alla system call listen");
        exit(0);
    }
    for(; ;){
        printf("\nserver in attesa.. \n");
        fflush(stdout);
        if((soa = accept(socketfd, (struct sockaddr*) &servizio, &froml)) == -1){
            printf("Chiamata fallita alla system call accept");
            exit(0);
        }
        read(soa, stringa, sizeof(stringa));
        printf("Ricevuto %s\n", stringa);
        parolaSenzaDoppieContinue(stringa);
        printf("Stringa nuova: %s", stringa);
        write(soa, &stringa, sizeof(stringa));
        close(soa);
    }
    close(socketfd);

    return 0;
}