import socket 

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(("127.0.0.1", 12345))
    lista_menu = client_socket.recv(1024).decode()
    print("Lista del menu: ", lista_menu)
    prodotto = input("Inserisci il prodotto che vuoi comprare: ")
    quantita = input("Inserisci il numero di prodotti che vuoi comprare: ")
    if not prodotto or not quantita.isdigit():
        print("Errore input inseriti")
        client_socket.close()
        return
    messaggio = prodotto + "," + quantita
    client_socket.sendall(messaggio.encode())
    risposta = client_socket.recv(1024).decode()
    print("Risposta del server: ", risposta)
    client_socket.close()

if __name__ == "__main__":
    start_client()