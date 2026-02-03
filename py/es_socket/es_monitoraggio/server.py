import socket
import threading

def gestione_meteo(conn, addr):
    print(f"Connessione con {addr}")
    
    while True:
        # 1. Ricevo i dati (tutto il blocco di testo inviato dal client)
        data = conn.recv(1024).decode()
        if not data:
            break
        
        # 2. Preparo una lista per mettere tutte le temperature trovate
        lista_temperature = []
        
        # 3. Analizzo il testo riga per riga
        # Il client manda: "Data;Temp1;Temp2" a capo "Data;Temp3;Temp4"...
        righe = data.strip().split("\n") 
        
        try:
            for riga in righe:
                if ";" in riga:
                    # Divido la riga usando il punto e virgola
                    pezzi = riga.split(";") 
                    # Il pezzo[1] è la temp delle 12, il pezzo[2] è quella delle 24
                    lista_temperature.append(float(pezzi[1]))
                    lista_temperature.append(float(pezzi[2]))
            
            # 4. Calcoli matematici
            if len(lista_temperature) > 0:
                media = sum(lista_temperature) / len(lista_temperature)
                massima = max(lista_temperature)
                minima = min(lista_temperature)
                
                # Creo la risposta
                risposta = (f"Giorni analizzati: {len(righe)}\n"
                            f"Media: {media:.2f} C\n"
                            f"Max: {massima} C\n"
                            f"Min: {minima} C")
            else:
                risposta = "Nessun dato valido trovato."

        except:
            risposta = "Errore nel formato dei dati."

        # 5. Invio la risposta
        conn.send(risposta.encode())
        
    conn.close()

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('0.0.0.0', 12345))
    server_socket.listen(5)
    print("Server Meteo pronto sulla porta 12345...")
    
    while True:
        conn, addr = server_socket.accept()
        t = threading.Thread(target=gestione_meteo, args=(conn, addr))
        t.start()

if __name__ == "__main__":
    start_server()