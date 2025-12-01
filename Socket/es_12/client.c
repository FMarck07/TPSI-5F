/*Scrivere il codice in C di un’applicazione socket CLIENT–SERVER in cui il server riceve in input una stringa e, 
dopo aver effettuato i controlli opportuni, rispedisce al client quattro valori interi:
il numero di lettere,
il numero di cifre,
il numero di spazi,
il numero di caratteri speciali presenti nella stringa.*/
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

    char str[DIM], alf[DIM], strINV[DIM], strCon[DIM];
    int socketfd, numero_vocali, scelta;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if((connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio))) == -1){
        printf("Chiamata fallita alla system call connect");
        exit(0);
    }


    printf("Inserisci una stringa: ");
    scanf("%s", str);

    write(socketfd, str, strlen(str) + 1); 

    printf("Cosa vuoi fare?\n");
    scanf("%d", &scelta); 
    
    write(socketfd, &scelta, sizeof(scelta)); 
    switch(scelta){
        case 1:
            read(socketfd, strINV, sizeof(strINV));
            printf("Stringa invertita dal server: %s\n", strINV);
            break;
        case 2:
            read(socketfd, &numero_vocali, sizeof(int));
            printf("Numero di vocali nella stringa: %d\n", numero_vocali);
            break;
        case 3:
            read(socketfd, alf, sizeof(alf));
            printf("Stringa con solo caratteri alfabetici dal server: %s\n", alf);
            break;
        case 4:
            read(socketfd, strCon, sizeof(strCon));
            printf("Stringa con tutte le vocali rimosse dal server: %s\n", strCon);
            break;
        default:
            printf("Scelta non valida.\n");
            break;
    }



    close(socketfd);
    return 0;
}