import socket
import threading
import time

def num_vocali(stringa):
    count = 0
    for c in stringa.lower():
        if c in "aeiou":
            count += 1
    return count
    
def caratteri_non_alfabetici(stringa):
    caratteri = ""
    for c in stringa.lower():
        if not c.isalpha():
            caratteri += c
    return caratteri

def function(conn, addr):
    print("Stabilita connessione con: ", addr)
    while True:
        stringa = conn.recv(1024).decode()
        if not stringa:
            break 
        numero_vocali = num_vocali(stringa)
        non_alf = caratteri_non_alfabetici(stringa)
        
        risposta = f"Numero di vocali {numero_vocali}"
        risposta2 = f"Caratteri non alfabetici{non_alf}"

        conn.send(risposta.encode())
        time.sleep(0.1)
        conn.send(risposta2.encode())
    conn.close()

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("127.0.0.1", 12345))
    server_socket.listen(5)
    print("Server in ascolto...")
    while True:
        conn, addr = server_socket.accept()
        thread = threading.Thread(target = function, args = (conn, addr))
        thread.start()
        
if __name__ == "__main__":
    start_server()