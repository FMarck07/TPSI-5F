import socket
import threading
lock = threading.Lock()

concerti = {
    "Travis Scott": {"data": "23/02/2027", "prezzo": 60, "posti": 8},
    "Drake": {"data": "12/10/2027", "prezzo": 50, "posti": 13},
    "IDK": {"data": "06/05/2026", "prezzo": 30, "posti": 3}
}

def funzione(conn, addr):
    print("Connessione stabilita con: ", addr)
    lista = ",".join(concerti.keys())
    conn.sendall(lista.encode())
    while True:
        data = conn.recv(1024).decode()
        if not data:
            break
        try:
            nome, numero = data.split(",")
            numero = int(numero)
        except:
            conn.sendall("Errore: input non valido".encode())
            continue
        if numero <= 0:
            risposta = "Numero biglietti non valido"
        else:
            with lock:
                if nome not in concerti:
                    risposta = "concerto non trovato"
                elif numero > concerti[nome]["posti"]:
                    risposta = "Non abbastanza posti disponibili"
                else:
                    prezzo = concerti[nome]["prezzo"]*numero
                    prezzo_scontato = numero * prezzo
                    sconto = 0
                    if numero > 1:
                        sconto = prezzo * 0.10
                        prezzo_scontato = prezzo - sconto
                        
                    concerti[nome]["posti"] -= numero
                    
                    risposta = f"""concerto: {nome}
                        data: {concerti[nome]['data']}
                        prezzo: {prezzo}
                        sconto: {sconto}
                        prezzo_scontato: {prezzo_scontato}
                        posti rimanenti: {concerti[nome]['posti']}"""
        conn.sendall(risposta.encode())
        
    conn.close()
                

def server_start():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("127.0.0.1", 12345))
    server_socket.listen(5)
    while True:
        conn, addr = server_socket.accept()
        thread = threading.Thread(target = funzione, args = (conn, addr))
        thread.start()

if __name__ == "__main__":
    server_start()