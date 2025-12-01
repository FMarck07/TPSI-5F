/*Scrivere il codice in C di un’applicazione socket CLIENT–SERVER in cui il server riceve in input una stringa e, 
dopo eventuali controlli, rispedisce al client due stringhe: 
la versione completamente in maiuscolo e la versione completamente in minuscolo della stringa ricevuta.*/
// SERVER

#include <ctype.h>      
#include <errno.h>      
#include <netinet/in.h> 
#include <stdio.h>      
#include <stdlib.h>    
#include <string.h>     
#include <sys/socket.h> 
#include <sys/types.h>  
#include <unistd.h> 

#define SERVERPORT 1450
#define DIM 100

void maiuscolo(char *str) {
    for (int i = 0; i<strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

void minuscolo(char *str){
    for(int i=0; i<strlen(str); i++){
        str[i] = tolower(str[i]);
    }
}

int main(int argc, char **argv){

    struct sockaddr_in servizio, remoto;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl (INADDR_ANY);
    servizio.sin_port = htons (SERVERPORT);

    char str[DIM], risposta[DIM], risposta2[DIM];
    int socketfd,soa, fromlen = sizeof(servizio);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&servizio, fromlen);
    listen(socketfd, 10);

    for(;;){
        printf("Server in ascolto...\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&remoto, &fromlen);
        read(soa, str, sizeof(str));
        
        maiuscolo(str);
        sprintf(risposta, "%s", str);

        minuscolo(str);
        sprintf(risposta2, "%s", str);
        
        write(soa, risposta, sizeof(risposta));
        write(soa, risposta2, sizeof(risposta2));
   
        close(soa);
    }

    return 0;
}

