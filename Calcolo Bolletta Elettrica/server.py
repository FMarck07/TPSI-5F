import threading
import socket

lock = threading.Lock()

# Dati: tariffa base (€/kWh), soglia per sovrapprezzo, sovrapprezzo oltre soglia (€/kWh)
tipi_utente = {
    "domestico": {"base": 0.20, "soglia": 300, "sovrapprezzo": 0.10},
    "azienda":   {"base": 0.25, "soglia": 500, "sovrapprezzo": 0.15}
}
IVA = 0.22

def gestisci_client(conn, addr):
    print("Connessione stabilita con:", addr)
    # Invia la lista dei tipi utente separata da virgole
    lista_tipi = ",".join(tipi_utente.keys())
    conn.sendall(lista_tipi.encode())

    while True:
        messaggio = conn.recv(1024).decode()
        if not messaggio:
            break
        try:
            tipo, kwh_str = messaggio.split(",")
            kwh = float(kwh_str)
        except:
            conn.sendall("Errore: formato non valido (es. domestico,350)".encode())
            continue

        if tipo not in tipi_utente:
            risposta = "Errore: tipo utente non valido"
        elif kwh <= 0:
            risposta = "Errore: i kWh devono essere > 0"
        else:
            with lock:
                info = tipi_utente[tipo]
                base = info["base"] * kwh
                if kwh > info["soglia"]:
                    eccedenza = kwh - info["soglia"]
                    sovrapprezzo = eccedenza * info["sovrapprezzo"]
                else:
                    sovrapprezzo = 0.0
                subtotale = base + sovrapprezzo
                iva = subtotale * IVA
                totale = subtotale + iva

                # Formato richiesto (uguale allo stile dell'albergo)
                risposta = f"""Tipo utente: {tipo}
kWh consumati: {kwh}
Costo base: {base:.2f} €
Sovrapprezzo: {sovrapprezzo:.2f} €
Subtotale: {subtotale:.2f} €
IVA (22%): {iva:.2f} €
Totale finale: {totale:.2f} €"""
        conn.sendall(risposta.encode())
    conn.close()

def avvia_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1", 12345))
    server.listen(5)
    print("Server in ascolto...")
    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=gestisci_client, args=(conn, addr))
        thread.start()

if __name__ == "__main__":
    avvia_server()
