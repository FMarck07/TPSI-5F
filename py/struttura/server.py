import socket
import threading

# --- 1. LOGICA DEL SINGOLO CLIENT (Eseguita in parallelo per ognuno) ---
def gestisci_client(conn, addr):
    # [SETUP INIZIALE: es. generare dati casuali, azzerare contatori]
    
    while True:
        try:
            # 1. Ricezione
            data = conn.recv(1024).decode()
            if not data: 
                break # Se il client si disconnette, esci dal ciclo
            
            # ==========================================
            # --- INIZIO LOGICA ESERCIZIO ---
            
            # Fai calcoli, controlli, if/elif sui 'data' ricevuti
            response = f"Hai inviato: {data}"
            
            # [Opzionale: if condizione_di_fine_gioco: break]
            
            # --- FINE LOGICA ESERCIZIO ---
            # ==========================================
            
            # 2. Invio Risposta
            conn.send(response.encode())
            
        except:
            break # Sicurezza in caso di errori di connessione
            
    conn.close()

# --- 2. MOTORE DEL SERVER ---
def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 12345))
    server_socket.listen(5)
    print("Server in ascolto...")
    
    while True:
        conn, addr = server_socket.accept()
        # Delega il lavoro al thread
        client_thread = threading.Thread(target=gestisci_client, args=(conn, addr))
        client_thread.start()

# Avvio effettivo dello script
if __name__ == "__main__":
    start_server()