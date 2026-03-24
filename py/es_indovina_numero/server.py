import socket
import threading
import random

def funzione(conn, addr):
    numero = random.randint(1, 100)
    print(f"Connessione stabilita con {addr}")
    while True:
        data = conn.recv(1024).decode()
        if not data:
            break
        guess = int(data)
        if guess == numero:
            response = "HAI VINTO!"
        elif guess > numero:
            response = "numero troppo alto!"
        else:
            response = "numero troppo basso!"
        conn.send(response.encode())
    conn.close()
    print(f"Connessione terminata con {addr}")

def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('127.0.0.1', 12345))
    server.listen(5)
    print("Server in ascolto...")
    while True:
        conn, addr = server.accept()
        client_thread = threading.Thread(target=funzione, args = (conn, addr))
        client_thread.start()

if __name__ == "__main__":
    start_server()
