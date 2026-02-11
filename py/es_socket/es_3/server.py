import socket
import threading

def gestisci_client(conn, addr):
    print(f"Connessione stabilita con {addr}")
    
    while True:
        try:
            data = conn.recv(1024).decode().strip()
            if not data:
                break

            # Separiamo i dati ricevuti
            giorno, temp12, temp24 = data.split("|")

            # Calcolo temperatura media
            media = (int(temp12) + int(temp24)) / 2

            response = (
                f"Dati ricevuti per {giorno}.\n"
                f"Temperatura media: {media:.1f}°C"
            )

            conn.send(response.encode())

        except Exception as e:
            print("Errore:", e)
            break

    conn.close()
    print(f"Connessione chiusa con {addr}")


def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("127.0.0.1", 12345))
    server_socket.listen(5)

    print("Server Meteo in ascolto sulla porta 12345...")

    while True:
        conn, addr = server_socket.accept()
        threading.Thread(target=gestisci_client, args=(conn, addr)).start()


if __name__ == "__main__":
    start_server()
