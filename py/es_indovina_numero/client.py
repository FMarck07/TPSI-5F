import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 12345))
    while True:
        guess = input("Inserisci un numero: ")
        client_socket.sendall(guess.encode())
        data = client_socket.recv(1024).decode()
        print(f"Datai rivetuti: {data}")
        if data == "HAI VINTO!":
            break
    client_socket.close()

if __name__ == "__main__":
    start_client()    