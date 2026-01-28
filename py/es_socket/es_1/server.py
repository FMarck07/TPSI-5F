import socket
import random
import threading

def gameInstance(conn, addr):
    number = random.randint(1, 100)
    print(f"Connsessione stabilita con {addr}")
    while 1:
        data = conn.recv(1024).decode()
        guess = int(data)
        if guess == number:
            response = "Hai vinto!"
            conn.send(response.encode())
            break
        elif guess > number:
            response = "Troppo alto!"
        elif guess < number:
            response = "Troppo basso!"

        conn.send(response.encode())
    conn.close()
    print(f"Connsessione terminata con{addr}")

def start_server():
    #inizializzazione lato server sulla socket

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 12345))
    server_socket.listen(10)
    print("Server in ascolto sulla porta... ")
    # loop che accetta le nuove connessioni
    while True:
        conn, addr = server_socket.accept()
        '''Inizializzazione Thread (Processo a sè 
        stante che esegue la funzione di gioco per l'istanza corrente)'''
        client_thread = threading.Thread(
            # target = funzione che il thread eseguirà
            target = gameInstance,
            # args = argomenti che verrranno passati alla funzione passata come target 
            args = (conn, addr)
        )
        client_thread.start()


if __name__ == "__main__":
    start_server()