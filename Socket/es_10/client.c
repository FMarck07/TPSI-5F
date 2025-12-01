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
    int lettere_out, cifre_out, spazi_out, speciali_out;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    char str[DIM];
    int socketfd;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if((connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio))) == -1){
        printf("Chiamata fallita alla system call connect");
        exit(0);
    }


    printf("Inserisci una stringa: ");
    scanf("%s", str);

    // Invio stringa: è meglio inviare la lunghezza effettiva + 1 (strlen)
    write(socketfd, str, strlen(str) + 1); 

    // 1. Riceve il conteggio delle lettere
    read(socketfd, &lettere_out, sizeof(int));
    
    // 2. Riceve il conteggio delle cifre
    read(socketfd, &cifre_out, sizeof(int));
    
    // 3. Riceve il conteggio degli spazi
    read(socketfd, &spazi_out, sizeof(int));
    
    // 4. Riceve il conteggio dei caratteri speciali
    read(socketfd, &speciali_out, sizeof(int));

    printf("\n--- Risultati Analisi Server ---\n");
    printf("Lettere: %d\n", lettere_out);
    printf("Cifre: %d\n", cifre_out);
    printf("Spazi: %d\n", spazi_out);
    printf("Caratteri Speciali: %d\n", speciali_out);

    close(socketfd);
    return 0;
}