import socket
def client_start():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 15000))
    nome = input("Inserisci il nome")
    numero_prenotazione = input("Inserisci il numero di tavoli che vuoi prenotare")
    messaggio = nome + "," + numero_prenotazione
    client_socket.sendall(messaggio.encode())
    risposta = client_socket.recv(1024).decode()
    print("Risposta del server: ", risposta)
    
    client_socket.close()
    
if __name__ == "__main__":
    client_start()