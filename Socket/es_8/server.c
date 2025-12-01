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

int ContaParole(char stringa[]){
    int count = 0;
    for(int i = 0; i<strlen(stringa); i++){
        if(stringa[i] == ' ' || stringa[i] == '\n'){
            count++;
        }
    }
    return count;
}

int main(){
    char stringa[256];
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    int socketfd, soa, froml = sizeof(servizio), parole = 0;
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
        parole = ContaParole(stringa);
        printf("Numero di parole presenti nella stringa: %d", parole);
        write(soa, &parole, sizeof(parole));
        close(soa);
    }
    close(socketfd);

    return 0;
}