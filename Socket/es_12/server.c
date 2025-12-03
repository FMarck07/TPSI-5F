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

int ContaVocali(char stringa[]){

    char a;

    int count = 0;

    for(int i = 0; i<strlen(stringa); i++){

        a = tolower(stringa[i]);

        if(a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u'){

            count++;

        }

    }

    return count;

}



void StringaInvertita(char str[]){

    int n = strlen(str);

    char temp;

    for(int i = 0; i < n / 2; i++){

        temp = str[i];

        str[i] = str[n - 1 - i];

        str[n - 1 - i] = temp;

    }

}



void SoloAlfabetici(char str[]){

    char a;

    int j = 0;

    for(int i = 0; i<strlen(str); i++){

        a = tolower(str[i]);

        if(!isalpha(a)){

            str[j] = str[i];

            j++;

        }

    }

    str[j] = '\0';

}



void RimuoviVocali(char str[]){

    char a;

    int j = 0;

    for(int i = 0; i<strlen(str); i++){

        a = tolower(str[i]);

        if(a != 'a' && a != 'e' && a != 'i' && a != 'o' && a != 'u'){

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
    int socketfd, soa, froml = sizeof(servizio), codice, numero_vocali;
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
        read(soa, stringa, sizeof(stringa) - 1);
        
        read(soa, &codice, sizeof(codice)); 
        
        printf("Ricevuto stringa: %s e codice: %d\n", stringa, codice);
        
        switch(codice){
            case 1:
                StringaInvertita(stringa);
                // Invia la lunghezza effettiva + terminatore
                write(soa, stringa, strlen(stringa) + 1); 
                break;
            case 2:
                numero_vocali = ContaVocali(stringa);
                write(soa, &numero_vocali, sizeof(numero_vocali));
                break;
            case 3:
                SoloAlfabetici(stringa);
                write(soa, stringa, strlen(stringa) + 1);
                break;
            case 4:
                RimuoviVocali(stringa);
                write(soa, stringa, strlen(stringa) + 1);
                break;
            default:
                printf("Codice non valido.\n");
                break;
        }
    }

    close(socketfd);
    return 0;
}
