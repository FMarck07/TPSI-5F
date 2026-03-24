import socket
import threading
lock = threading.Lock()

menu = {
    "pizza":{"prezzo": 7},
    "humburger":{"prezzo": 8},
    "risotto":{"prezzo": 12}
}

def funzione(conn, addr):
    print("Stabilita connessione con ", addr)
    lista_menu = ",".join(menu.keys())
    conn.sendall(lista_menu.encode())
    while True:
        risposta = conn.recv(1024).decode()
        if not risposta:
            break
        try:
            prodotto, quantita = risposta.split(",")
            quantita = int(quantita)
        except:
            conn.send("Errore input".encode())
            continue
        if not prodotto in menu:
            risposta = "Nessun prodotto col nome inserito"
        elif quantita <= 0:
            risposta = "Quantita non consetita"
        else:
            with lock:
                prezzo = menu[prodotto]["prezzo"] * quantita
                sconto = 0
                prezzo_finale = prezzo
                if quantita > 3:
                    sconto = prezzo*0.10
                    prezzo_finale -= sconto
                
                risposta = f"""prodotto: {prodotto}
quantita: {quantita}
prezzo: {prezzo}
sconto: {sconto}
prezzo scontato: {prezzo_finale}"""
        
        conn.sendall(risposta.encode())
    conn.close()
    

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("127.0.0.1", 12345))
    server_socket.listen(5)
    while True:
        conn, addr = server_socket.accept()
        thread = threading.Thread(target = funzione, args = (conn, addr))
        thread.start()

if __name__ == "__main__":
    start_server()