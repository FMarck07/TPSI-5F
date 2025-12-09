/*
  Scrivere il codice in C di un’applicazione socket CLIENT–SERVER.
  Il client invia al server una stringa e un codice di operazione (0, 1, 2, 3).
  Il server, in base al codice ricevuto, elabora la stringa e restituisce:

  Operazioni

  0 → Convertire la stringa in MAIUSCOLO

  1 → Restituire la lunghezza della stringa (numero di caratteri)

  2 → Contare il numero di cifre (0–9) presenti nella stringa

  3 → Restituire la stringa con gli spazi sostituiti da '_' (underscore)
*/
//SERVER
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#define DIM 100
#define SERVERPORT 1450

void Maiuscolo(char stringa[]){
    for(int i=0;i<strlen(stringa);i++){
        stringa[i] = toupper(stringa[i]);
    }
}

int Lunghezza(char stringa[]){
    return sizeof(stringa);
}

int NCifre(char stringa[]){
    int numeroCifre = 0;
    for(int i=0; i<strlen(stringa);i++){
        if(isdigit(stringa[i])){
            numeroCifre++;
        }
    }
    return numeroCifre;
}

void StringaCastrata(char stringa[]){
    for(int i=0; i<strlen(stringa);i++){
        if(stringa[i]== ' '){
            stringa[i] = '_';
        }
    }
}

int main(){
    struct sockaddr_in servizio;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd,soa,opzione,len= sizeof(servizio);
    char stringa[DIM];

    if( (socketfd = socket(AF_INET,SOCK_STREAM,0))== -1){
        printf("Hai sbagliato coglione");
        exit(1);
    }

    if(bind (socketfd,(struct sockaddr*)&servizio,sizeof(servizio)) == -1){
        printf("Ma porco di dio");
        exit(1);
    }
    
    if(listen(socketfd,10)== -1){
        printf("GG");
        exit(1);
    }

    for(;;){
    
        soa = accept(socketfd,(struct sockaddr*)&servizio,&len);
        if(soa == -1){
            printf("Errore soa");
            exit(1);
        }

        read(soa,stringa,sizeof(stringa));
        read(soa,&opzione,sizeof(opzione));

        switch (opzione){
            case 0: 
                Maiuscolo(stringa);
            break;

            case 1: 
                sprintf(stringa,"Lunghezza della stringa %d",Lunghezza(stringa));
            break;

            case 2: 
                sprintf(stringa,"Numero di cifre %d",NCifre(stringa));
            break;

            case 3: 
                StringaCastrata(stringa);
            break;

            default: 
                printf("Eh ma sei coglione allora");
            break;
        }

        write(soa,stringa, sizeof(stringa));
        close(soa);
    }
    return 0;
}
