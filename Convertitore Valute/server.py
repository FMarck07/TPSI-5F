import threading
import socket

# Tassi di cambio rispetto a EUR (base)
TASSI = {
    "EUR": 1.0,
    "USD": 1.08,
    "GBP": 0.86,
    "JPY": 169.0,
    "CHF": 0.96
}

def converti(valuta_orig, valuta_dest, importo):
    if importo <= 0:
        return "Errore: l'importo deve essere > 0"
    if valuta_orig not in TASSI or valuta_dest not in TASSI:
        return "Errore: valuta non valida (usa EUR, USD, GBP, JPY, CHF)"
    
    # Converti in EUR, poi nella valuta destinazione
    in_eur = importo / TASSI[valuta_orig]
    risultato = in_eur * TASSI[valuta_dest]
    return f"{importo:.2f} {valuta_orig} = {risultato:.2f} {valuta_dest}"

def gestisci_client(conn, addr):
    print(f"Connessione da {addr}")
    while True:
        data = conn.recv(1024).decode()
        if not data:
            break
        parti = data.split(",")
        if len(parti) != 3:
            conn.sendall("Errore: formato valuta_orig,valuta_dest,importo".encode())
            continue
        valuta_orig, valuta_dest, importo_str = parti
        try:
            importo = float(importo_str)
        except ValueError:
            conn.sendall("Errore: importo non valido".encode())
            continue
        risposta = converti(valuta_orig.strip().upper(), valuta_dest.strip().upper(), importo)
        conn.sendall(risposta.encode())
    conn.close()

def avvia_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1", 12345))
    server.listen(5)
    print("Server Convertitore in ascolto...")
    while True:
        conn, addr = server.accept()
        threading.Thread(target=gestisci_client, args=(conn, addr)).start()

if __name__ == "__main__":
    avvia_server()
