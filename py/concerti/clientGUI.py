import socket
import tkinter as tk
from tkinter import messagebox

# 1. Connessione iniziale
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 12345))

data = client_socket.recv(1024).decode()
lista_concerti = data.split(",")

def acquista():
    nome = variabile_tendina.get()
    n_posti = entry_posti.get()
    if not nome or not n_posti.isdigit():
        messagebox.showerror("errore", "input non validi")
        entry_posti.delete(0, tk.END)
        return
    message = nome + "," + n_posti
    client_socket.sendall(message.encode())
    risposta = client_socket.recv(1024).decode()
    messagebox.showinfo("Risposta del server: ", risposta)
    entry_posti.delete(0, tk.END)

root = tk.Tk()
root.title("Gestisci concerti")
frame = tk.Frame(root, pady = 20, padx = 20)
frame.pack()
label = tk.Label(frame, text = "Seleziona il concerto dalla lista")
label.pack()
variabile_tendina = tk.StringVar(root)
variabile_tendina.set(lista_concerti[0])

menu_concerti = tk.OptionMenu(frame, variabile_tendina, *lista_concerti)
menu_concerti.pack(pady = 5)

label_posti = tk.Label(frame, text="Inserisci il numero di biglietti:")
label_posti.pack()
entry_posti = tk.Entry(frame, width=20)
entry_posti.pack(pady=5)

btn = tk.Button(frame, text="Acquista Biglietti", command=acquista)
btn.pack(pady=15)

root.mainloop()
client_socket.close()
