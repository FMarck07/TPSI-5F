//CLIENT
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

//Client: Socket, connect

int main()
{
    
    struct sockaddr_in servizio; 
    int socketfd, numeroParole;
    char str[256];
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Chiamata fallita");
        exit(1);
    }
    
    if(connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) == -1){
        printf("Chiamata fallita");
        exit(1);
    }
    
    printf("Inserisci una stringa: ");
    fgets(str, sizeof(str), stdin);
    write(socketfd, str, strlen(str) + 1); 

    read(socketfd, &numeroParole, sizeof(int));
    printf("Numero di parole nella stringa inviata: %d\n", numeroParole);
    close(socketfd);
    
    return 0;
}