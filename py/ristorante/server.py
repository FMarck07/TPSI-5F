import socket
import threading

posti_totali = 20

def funzione(conn, addr):
    global posti_totali
    
    while True:
        messaggio = conn.recv(1024).decode()
        if not messaggio:
            break
        nome, posti = messaggio.split(",")
        posti = int(posti)
        if posti_totali >= posti:
            posti_totali -= posti
            risposta = f"Numero posti disponibili {posti_totali}"
        else:
            risposta = "Numero posti disponibili insufficienti"
        conn.send(risposta.encode())
    
    conn.close()

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 15000))
    server_socket.listen(5)
    while True:
        conn, addr = server_socket.accept()
        thread = threading.Thread(target = funzione, args = (conn, addr))
        thread.start()
        
if __name__ == "__main__":
    start_server()