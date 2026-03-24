import socket
import tkinter as tk
from tkinter import messagebox

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(("127.0.0.1", 12345))
#guardare
ricevuto = client_socket.recv(1024).decode()
lista_camere = ricevuto.split(",")

def start_client():
    camera = variabile.get()
    n_notti = entry_notti.get()

    if not camera or not n_notti.isdigit():
        messagebox.showerror("errore", "Inserisci un input valido")
        entry_notti.delete(0, tk.END)
        return
    messaggio = camera + "," + n_notti
    client_socket.sendall(messaggio.encode())
    risposta = client_socket.recv(1024).decode()
    messagebox.showinfo("risposta del server: ", risposta)
    entry_notti.delete(0, tk.END)

root = tk.Tk()
root.title("Gestione albergo")

frame = tk.Frame(root, pady = 20, padx = 20)
frame.pack()

variabile = tk.StringVar(root)
variabile.set(lista_camere[0])

menu = tk.OptionMenu(frame, variabile, *lista_camere)
menu.pack(pady = 15)

label = tk.Label(frame, text = "Inserisci il numero di notti")
label.pack(pady = 10)
entry_notti = tk.Entry(frame, width = 40)
entry_notti.pack(pady = 10)

btn = tk.Button(frame, text = "Invia i dati", command = start_client)
btn.pack(pady = 10)
root.mainloop()

client_socket.close()