import threading
import socket
lock = threading.Lock()
#guardare
camere = {
    "singola": {"prezzo" : 50, "n_camere" : 8},
    "doppia": {"prezzo": 70, "n_camere": 6},
    "suit": {"prezzo": 150, "n_camere": 3},
}

def function(conn, addr):
    print("Connessione stabilita con: ", addr)
    lista_camere = ",".join(camere.keys())
    conn.sendall(lista_camere.encode())
    while True:
        messaggio_ricevuto = conn.recv(1024).decode()
        if not messaggio_ricevuto:
            break
        try:
            camera, n_notti = messaggio_ricevuto.split(",")
            n_notti = int(n_notti)
        except:
            conn.sendall("errore input".encode())
            continue
        if camera not in camere:
            risposta = "Errore: Camera non trovata"
        elif camere[camera]["n_camere"] <= 0:
            risposta = "Non ci sono + camere"
        elif n_notti <= 0:
            risposta = "Numero di notti inserite non valide"
        else:
            with lock:
                camere[camera]["n_camere"] -= 1
                prezzo = camere[camera]["prezzo"] * n_notti
                sconto = 0
                prezzo_finale = prezzo
                if n_notti > 3:
                    sconto = prezzo*0.10
                    prezzo_finale -= sconto
                    
                risposta = f"""camara: {camera}
numero notti: {n_notti}
prezzo: {prezzo}
sconto: {sconto}
prezzo scontato: {prezzo_finale}
posti rimanenti: {camere[camera]['n_camere']}"""
            
        conn.sendall(risposta.encode())
    conn.close()

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("127.0.0.1", 12345))
    server_socket.listen(5)
    print("Server in ascolto... ")
    while True:
        conn, addr = server_socket.accept()
        thread = threading.Thread(target = function, args = (conn, addr))
        thread.start()

if __name__ == "__main__":
    start_server()

