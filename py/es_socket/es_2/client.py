import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # SE SEI IN LAN CAMBIA 'localhost' CON L'IP DEL SERVER
    client_socket.connect(('localhost', 12345))
    
    while True:
        print("\n--- PRENOTAZIONE TAXI ---")
        partenza = input("Citta di partenza: ")
        arrivo = input("Citta di arrivo: ")

        # Dà errore se la partenza è un numero OPPURE se l'arrivo è un numero
        # (Vogliamo che siano parole, non numeri)
        if partenza.isdigit() or arrivo.isdigit():
            print("Errore: Inserisci nomi di città validi (non numeri).")
            continue
        
        # Invio (uso la virgola come separatore)
        messaggio = partenza + "," + arrivo
        client_socket.sendall(messaggio.encode())
        
        # Ricezione
        risposta = client_socket.recv(1024).decode()
        print("Risposta dal server: " + risposta)
        
        if risposta == "Non ci sono taxi disponibili.":
            break
            
    client_socket.close()

if __name__ == "__main__":
    start_client()