import socket 
import tkinter as tk
from tkinter import messagebox

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 12345))

def gameInterface():
    guess = entry.get()

    if not guess.isdigit():
        messagebox.showerror("Errore", "Inserisci un numero valido")
        return
    client_socket.sendall(guess.encode())

    response = client_socket.recv(1024).decode()
    messagebox.showinfo("Risposta dal server", response)

    if response == "Hai vinto!":
        client_socket.close()
        root.destroy()

    entry.delete(0, tk.END)

root = tk.Tk()
root.title("Gioco dei numeri")

label = tk.Label(root, text = "Inserisci un numero")
label.pack(pady = 5)

entry = tk.Entry(root)
entry.pack(pady = 5)

button = tk.Button(root, text = "Invio", comand = gameInterface)
button.pack(pady=10)

root.mainloop()