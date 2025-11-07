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

// Funzione per ordinare alfabeticamente una stringa
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

        read(soa, str, DIM);   // si assume che il client invii '\0' finale

        printf("\nStringa ricevuta: %s\n", str);

        ordina_stringa(str);

        printf("Stringa ordinata: %s\n", str);

        write(soa, str, sizeof(str));

        close(soa);
    }

    close(socketfd);
    return 0;
}
