import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 12345))
    data = client_socket.recv(1024).decode()
    lista_veicolo = data.split(",")
    print("Veicoli disponibili: ", lista_veicolo)
    veicolo = input("Inserisci il nome del veicolo: ")
    n_ore = input("Inserisci il numero di ore: ")
    if not veicolo or not n_ore.isdigit():
        print("errore", "Input non validi")
        client_socket.close()
        return
    messaggio = veicolo + "," + n_ore
    client_socket.sendall(messaggio.encode())
    risposta = client_socket.recv(1024).decode()
    print("Risposta del server: ", risposta)
    client_socket.close()

if __name__ == "__main__":
    start_client()
    
