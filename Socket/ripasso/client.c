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
//CLIENT
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

int main(){
  struct sockaddr_in servizio;

  servizio.sin_family = AF_INET;
  servizio.sin_addr.s_addr = htonl(INADDR_ANY);
  servizio.sin_port = htons(SERVERPORT);

  int socketfd,opzione;
  char stringa[DIM];


  if((socketfd = socket(AF_INET,SOCK_STREAM,0))== -1){
    printf("Chiamata fallita");
    exit(1);
  }

  if(connect (socketfd,(struct sockaddr*)&servizio,sizeof(servizio))== -1){
    printf("Astolfi gay");
    exit(1);
  }

  printf("Inserisci sta cazzo di stringa");
  fgets(stringa, DIM, stdin);

  printf("Inserisci un opzione");
  scanf("%d", &opzione);

  write(socketfd,stringa,sizeof(stringa));
  write(socketfd,&opzione,sizeof(opzione));

  read(socketfd,stringa,sizeof(stringa));

  printf("Risposta del server: %s",stringa);
  close(socketfd);
}
