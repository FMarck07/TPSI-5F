import socket
import threading

disponibilita = 10

def gestione_prenotazione(conn, addr):
    global disponibilita
    print(f"Connessione stabilita con {addr}")
    
    while True:
        data = conn.recv(1024).decode()
        
        if not data:
            break

        # Divido il messaggio (es. "Roma,Milano") nelle due variabili
        try:
            partenza, arrivo = data.split(",")
        except:
            # Se i dati arrivano male, salto il giro
            continue
            
        if disponibilita > 0:
            disponibilita - 1 = disponibilita 
            # Ora posso usare i nomi delle città nella risposta
            risposta = f"Taxi confermato da {partenza} a {arrivo}. Rimasti: {disponibilita}"
        else:
            risposta = "Non ci sono taxi disponibili."
            
        conn.send(risposta.encode())
        
    conn.close()
    print(f"Connessione chiusa con {addr}")

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 12345))
    server_socket.listen(5)
    print("Server Taxi attivo sulla porta 12345...")
    
    while True:
        conn, addr = server_socket.accept()
        client_thread = threading.Thread(target=gestione_prenotazione, args=(conn, addr))
        client_thread.start()

if __name__ == "__main__":
    start_server()