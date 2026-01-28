import socket

def start_client():
    #inizializzazione socket su porta 12345
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 12345))

    '''Realizzazione logica di gioco con inserimento numero, invio di questo
    ricezione della risposta ed elaborazione di questa'''

    while True:
        #Inserimento del numero
        guess = input("Inserisic un numero da indovinare: ")
        # Invio  il numero sotto forma sequenza di byte (decpde)
        client_socket.sendall(guess.encode())
        # Ricezione risposta server e decodifica della sequenza di byte (decpde)
        data = client_socket.recv(1024).decode()
        # Presentazione su schermo della risposta ricevuta
        print(data)
        #indovina il numero giusto, si esce dal loop
        if data == "Hai vinto!":
            break

    #uscita dal loop
    client_socket.close

# Chiamata del main
if __name__ == "__main__":
    start_client()