import socket
import threading
lock = threading.Lock()

mezzi = {
    "Monopattino": {"prezzo": 5, "disponibilita": 10},
    "Bici": {"prezzo": 8, "disponibilita": 5},
    "Scooter": {"prezzo": 15, "disponibilita": 3},
}

def veicolo(conn, addr):
    print("Stabilita connessione con: ", addr)
    
    lista = ",".join(mezzi.keys())
    conn.sendall(lista.encode())
    while True:
        ricevuto = conn.recv(1024).decode()
        if not ricevuto:
            break
        try:
            nome_veicolo, numero_ore = ricevuto.split(",")
            numero_ore = int(numero_ore)
        except:
            conn.sendall("Errore input".encode())
            continue
        if numero_ore <= 0:
            risposta = "Numero di ore non valido"
        elif mezzi[nome_veicolo]["disponibilita"] < 1:
            risposta = f"Non ci sono + {nome_veicolo} disponibili"
        
        else:
            with lock:
                mezzi[nome_veicolo]["disponibilita"] -= 1 
                prezzo = mezzi[nome_veicolo]["prezzo"]*numero_ore
                sconto = 0
                prezzo_finale = prezzo
                if numero_ore > 5:
                    sconto = prezzo * 0.20
                    prezzo_finale -= sconto
        
            risposta = f"""Veicolo scelto: {nome_veicolo}
                Ore prenotate: {numero_ore}
                prezzo: {prezzo}
                sconto {sconto}
                prezzo_finale {prezzo_finale}
                veicolo rimanenti {mezzi[nome_veicolo]['disponibilita']}"""
        
            
        conn.sendall(risposta.encode())
    conn.close()    

    

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("127.0.0.1", 12345))
    server_socket.listen(5)
    while True:
        conn, addr = server_socket.accept()
        thread = threading.Thread(target = veicolo, args = (conn, addr))
        thread.start()
    
if __name__ == "__main__":
    start_server()