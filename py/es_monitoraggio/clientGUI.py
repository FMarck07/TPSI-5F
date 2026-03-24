import socket
import tkinter as tk
from tkinter import messagebox

# Connessione al server (come nel tuo esempio Taxi)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 12345))

def invia_dati():
    # 1. Prendo il testo dalla casella grande
    # "1.0" significa dall'inizio, "end" significa alla fine
    messaggio = text_area.get("1.0", tk.END).strip()
    
    if messaggio:
        # 2. Invio
        client_socket.sendall(messaggio.encode())
        
        # 3. Ricevo risposta
        risposta = client_socket.recv(1024).decode()
        
        # 4. Mostro risposta
        messagebox.showinfo("Risultati Meteo", risposta)

# --- CREAZIONE INTERFACCIA ---
root = tk.Tk()
root.title("Stazione Meteo")
root.geometry("400x350")

# Etichetta
lbl = tk.Label(root, text="Inserisci dati (Giorno;Temp12;Temp24):")
lbl.pack(pady=5)

# Area di testo grande (per incollare più giorni)
text_area = tk.Text(root, height=10, width=40)
text_area.pack(pady=5, padx=10)
# Esempio pre-scritto per facilitare il test
text_area.insert("1.0", "01/03/2025;18.5;16.2\n02/03/2025;19.1;17.0\n03/03/2025;20.0;18.4")

# Bottone
btn = tk.Button(root, text="Invia Dati", command=invia_dati)
btn.pack(pady=20)

root.mainloop()