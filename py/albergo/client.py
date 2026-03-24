import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(("127.0.0.1", 12345))
    lista_camere = client_socket.recv(1024).decode()
    print("Lista camere: ", lista_camere)
    camera = input("Inserisci la camera che vuoi prenotare")
    n_notti = input("Inserisci il numero di notti")
    if not camera or not n_notti.isdigit():
        print("Errore nell'input")
        client_socket.close()
        return
    messaggio = camera + "," + n_notti
    client_socket.sendall(messaggio.encode())
    risposta = client_socket.recv(1024).decode()
    print("Risposta del server: ", risposta)

if __name__ == "__main__":
    start_client()
