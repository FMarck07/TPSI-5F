import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 12345))

    while True:
        # 1. Input dell'utente
        messaggio = input("Inserisci dato: ")
        
        # 2. Invio al server
        client_socket.sendall(messaggio.encode())
        
        # 3. Ricezione dal server
        risposta = client_socket.recv(1024).decode()
        print(risposta)
        
        # ==========================================
        # --- LOGICA ESERCIZIO (Condizione di uscita) ---
        # if risposta == "Hai vinto!" oppure messaggio == "esci":
        #     break 
        # ==========================================

    client_socket.close()

if __name__ == "__main__":
    start_client()