/*
Esercizio 3
Scrivere il codice in C di un'applicazione Socket CLIENT-SERVER in cui il server riceve in input 1 stringa
e, dopo gli opportuni controlli, rispedisce al Client la stringa ordinata alfabeticamente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 100
#define SERVERPORT 1313

// Funzione per ordinare alfabeticamente una stringa (bubble sort)
void ordina_stringa(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tolower(str[i]) > tolower(str[j])) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main() {
    int socketfd, soa;
    struct sockaddr_in servizio, addr_remoto;
    socklen_t fromlen = sizeof(addr_remoto);
    char str[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Errore creazione socket");
        exit(1);
    }

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    if (bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) < 0) {
        perror("Errore nel bind");
        close(socketfd);
        exit(1);
    }

    listen(socketfd, 10);
    printf("Server avviato. In ascolto sulla porta %d...\n", SERVERPORT);

    for (;;) {
        soa = accept(socketfd, (struct sockaddr*)&addr_remoto, &fromlen);
        if (soa < 0) {
            perror("Errore nella accept");
            continue;
        }

        memset(str, 0, DIM);
        read(soa, str, DIM);

        printf("\nStringa ricevuta: %s\n", str);

        ordina_stringa(str);

        printf("Stringa ordinata: %s\n", str);

        write(soa, str, strlen(str) + 1);

        close(soa);
    }

    close(socketfd);
    return 0;
}
