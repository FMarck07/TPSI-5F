import socket
import tkinter as tk
from tkinter import messagebox

# 1. Connessione iniziale
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 12345))
data = client_socket.recv(1024).decode()
lista_veicolo = data.split(",")

def funzione():
    veicolo = variablile.get()
    n_ore = entry_ore.get()
    if not veicolo or not n_ore.isdigit():
        messagebox.showerror("errore", "Input non validi")
        entry_ore.delete(0, tk.END)
        return
    messaggio = veicolo + "," + n_ore
    client_socket.sendall(messaggio.encode())
    risposta = client_socket.recv(1024).decode()
    messagebox.showinfo("Risposta del server: ", risposta)
    entry_ore.delete(0, tk.END)
    
root = tk.Tk()
root.title("Gestione vendita veicoli")

frame = tk.Frame(root, pady = 20, padx = 20)
frame.pack()

variablile = tk.StringVar(root)
variablile.set(lista_veicolo[0])

menu = tk.OptionMenu(frame, variablile, *lista_veicolo)
menu.pack(pady = 10)

label = tk.Label(frame, text = "Inserisci il numero di ore")
label.pack()
entry_ore = tk.Entry(frame, width = 40)
entry_ore.pack(pady = 10)

btn = tk.Button(frame, text = "Invia i dati", command = funzione)
btn.pack(pady = 10)

root.mainloop()
client_socket.close()
