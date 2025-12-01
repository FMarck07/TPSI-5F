/*Scrivere il codice in C di un’applicazione socket CLIENT–SERVER in cui il server riceve in input una stringa e, dopo eventuali controlli, 
rispedisce al client due stringhe: la versione completamente in maiuscolo e la versione completamente in minuscolo della stringa ricevuta.*/
// CLIENT
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

int main(){

    struct sockaddr_in servizio;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    char str[DIM], maiuscolo[DIM], minuscolo[DIM];
    int socketfd;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    printf("Inserisci una stringa: ");
    scanf("%s", str);

    write(socketfd, str, strlen(str) + 1);

    read(socketfd, str, sizeof(str));

    printf("Stringa ricevuta: %s\n", str);

    close(socketfd);
    return 0;
}