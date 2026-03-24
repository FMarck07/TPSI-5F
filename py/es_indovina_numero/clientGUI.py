import tkinter as tk
from tkinter import messagebox
import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 12345))
def funzione():
    guess = entry.get()
    if not guess.isdigit():
        messagebox.showerror("Errore", "Inserisci un numero valido!")
        return
    client_socket.sendall(guess.encode())
    data = client_socket.recv(1024).decode()
    messagebox.showinfo("Risposta dal server", data)
    
    if data == "Hai vinto!":
        client_socket.close()
        root.destroy()

    entry.delete(0, tk.END)


# --- 3. CREAZIONE INTERFACCIA (Il "Motore" della GUI) ---
root = tk.Tk()
root.title("Titolo Esercizio")

# Frame per contenere gli elementi grafici (solo estetica)
frame = tk.Frame(root, padx=20, pady=20)
frame.pack()

# Etichetta
label = tk.Label(frame, text="Inserisci messaggio:")
label.pack()

# Casella di input
entry = tk.Entry(frame, width=40)
entry.pack(pady=10)

# Pulsante che richiama invia_messaggio()
btn = tk.Button(frame, text="Invia al server", command=funzione)
btn.pack()

# Avvia il loop grafico della finestra
root.mainloop()