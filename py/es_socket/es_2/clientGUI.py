import socket
import tkinter as tk
from tkinter import messagebox

# Connessione al server (fatta all'avvio come nel tuo esempio)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# INSERISCI QUI L'IP DEL SERVER SE SEI SU UN ALTRO PC
client_socket.connect(('localhost', 12345))

def invia_richiesta():
    part = entry_partenza.get()
    arr = entry_arrivo.get()
    
    # Controllo input
    if not part or not arr or not part.isalpha() or not arr.isalpha():
        messagebox.showerror(
        "Errore",
        "Inserisci solo nomi di città (solo lettere)."
    )
        entry_partenza.delete(0, tk.END)
        entry_arrivo.delete(0, tk.END)
        return 
    
    # Creo il messaggio
    messaggio = part + "," + arr
    
    # Invio al server
    client_socket.sendall(messaggio.encode())
    
    # Ricevo risposta
    risposta = client_socket.recv(1024).decode()
    
    # Mostro risposta
    messagebox.showinfo("Risposta Server", risposta)
    
    # Pulisco le caselle
    entry_partenza.delete(0, tk.END)
    entry_arrivo.delete(0, tk.END)

# Creazione Finestra
root = tk.Tk()
root.title("Prenotazione Taxi")

# Etichetta e Casella Partenza
label1 = tk.Label(root, text="Citta di Partenza")
label1.pack(pady=5)
entry_partenza = tk.Entry(root)
entry_partenza.pack(pady=5)

# Etichetta e Casella Arrivo
label2 = tk.Label(root, text="Citta di Arrivo")
label2.pack(pady=5)
entry_arrivo = tk.Entry(root)
entry_arrivo.pack(pady=5)

# Bottone
button = tk.Button(root, text="Invia Richiesta", command=invia_richiesta)
button.pack(pady=20)

root.mainloop()