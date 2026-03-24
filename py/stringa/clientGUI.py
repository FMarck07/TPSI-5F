import tkinter as tk
from tkinter import messagebox
import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(("127.0.0.1", 12345))

def function():
    stringa = entry_stringa.get()
    if not stringa:
        messagebox.showerror("errore", "Inserisci una stringa valida")
        entry_stringa.delete(0, tk.END)
        return
    client_socket.sendall(stringa.encode())
    risposta = client_socket.recv(1024).decode()
    risposta2 = client_socket.recv(1024).decode()
    messagebox.showinfo("Risposta server", risposta)
    messagebox.showinfo("Risposta 2 server", risposta2)
    entry_stringa.delete(0, tk.END)
    

root = tk.Tk()
root.title("Elaborazione stringa")

frame = tk.Frame(root, pady = 20, padx = 20)
frame.pack()

label = tk.Label(frame, text = "Inserisci la stringa")
label.pack()
entry_stringa = tk.Entry(frame, width = 40)
entry_stringa.pack(pady = 10)

btn = tk.Button(frame, text = "Invia i dati", command = function)
btn.pack()

root.mainloop()
