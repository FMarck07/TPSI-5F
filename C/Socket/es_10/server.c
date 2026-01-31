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

void conta(char str[], int *lettere, int *cifre, int *spazi, int *caratteri_speciali){
    for(int i = 0; i<strlen(str); i++){
        if(isalpha(str[i])){
            (*lettere)++;
        }else if(isdigit(str[i])){
            (*cifre)++;
        }else if(str[i] == ' '){
            (*spazi)++;
        }else{
            (*caratteri_speciali)++;
        }
    }
}

int main(){

    struct sockaddr_in servizio, remoto;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl (INADDR_ANY);
    servizio.sin_port = htons (SERVERPORT);

    char str[DIM];
    int socketfd,soa, fromlen = sizeof(servizio), lettere, cifre, spazi, caratteri_speciali;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) { perror("socket failed"); exit(EXIT_FAILURE); }
    
    if (bind(socketfd, (struct sockaddr *)&servizio, fromlen) < 0) { perror("bind failed"); exit(EXIT_FAILURE); }
    
    if (listen(socketfd, 10) < 0) { perror("listen failed"); exit(EXIT_FAILURE); }

    for(;;){
        printf("Server in ascolto...\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&remoto, (socklen_t*)&fromlen);
        if (soa < 0) { perror("accept failed"); continue; } 

        read(soa, str, DIM - 1);
        printf("Stringa ricevuta: %s\n", str);

        // Reset dei contatori per la nuova connessione
        lettere = 0;
        cifre = 0;
        spazi = 0;
        caratteri_speciali = 0;

        conta(str, &lettere, &cifre, &spazi, &caratteri_speciali);
        
        printf("Risultati: Lettere=%d, Cifre=%d, Spazi=%d, Speciali=%d\n", lettere, cifre, spazi, caratteri_speciali);
        
        // Invio dei quattro interi come dati grezzi
        write(soa, &lettere, sizeof(int));
        write(soa, &cifre, sizeof(int));
        write(soa, &spazi, sizeof(int));
        write(soa, &caratteri_speciali, sizeof(int));
    
        close(soa);
    }

    return 0;
}