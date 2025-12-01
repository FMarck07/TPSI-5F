// client invia una stringa server restituisce la stringa in cui le vocali sono sostituite da una lettera x
// esempio: ciao  restituita cXXX


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

void sostituzione(char stringa[]){
    for(int i = 0; i < strlen(stringa); i++){
        if(stringa[i] == 'a' || stringa[i] == 'e' || stringa[i] == 'i' || stringa[i] == 'o' || stringa[i] == 'u'){
            stringa[i] = 'x';
        }
    }
}

int main(){
    struct sockaddr_in servizio;
    char stringa[20];
    int socketfd, soa, fromlen = sizeof(servizio);
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
    if(bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) == -1){
        printf("Chiamata fallita alla system call bind");
        exit(0);
    }
    if(listen(socketfd, 10) == -1){
        printf("Chiamata fallita alla system call listen");
        exit(0);
    }
    while(1){
        printf("\nserver in attesa.. \n");
        // accetazione del collegamento
        if ((soa = accept(socketfd, (struct sockaddr *)&servizio, &fromlen)) == -1) {
            printf("Chiamata fallita alla system call accept");
            exit(0);
        }
        // leggo stringa proveniente dalla socket
        read(soa, stringa, sizeof(stringa));
        printf("Ricevuto %s\n", stringa);
        sostituzione(stringa);
        printf("Stringa convertita: %s\n", stringa);

        write(soa, stringa, sizeof(stringa));
        close(soa);
    }
    return 0;
}
