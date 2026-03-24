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

frame = tk.Frame(root, padx=20, pady=20)
frame.pack()

# Etichetta e Casella Partenza
label1 = tk.Label(frame, text="Citta di Partenza")
label1.pack()
entry_partenza = tk.Entry(frame, width = 40)
entry_partenza.pack(pady = 10)

# Etichetta e Casella Arrivo
label2 = tk.Label(frame, text="Citta di Arrivo")
label2.pack()
entry_arrivo = tk.Entry(frame, width = 40)
entry_arrivo.pack(pady = 10)

# Bottone
button = tk.Button(frame, text="Invia Richiesta", command=invia_richiesta)
button.pack()

root.mainloop()