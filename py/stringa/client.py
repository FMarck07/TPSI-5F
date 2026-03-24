import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(("127.0.0.1", 12345))
    stringa = input("Inserisci una stringa: ")
    client_socket.sendall(stringa.encode())
    risposta = client_socket.recv(1024).decode()
    risposta2 = client_socket.recv(1024).decode()
    print("Risposta1 del server: ", risposta)
    print("Risposta2 del server: ", risposta2)
    client_socket.close()
    
if __name__ == "__main__":
    start_client()
    