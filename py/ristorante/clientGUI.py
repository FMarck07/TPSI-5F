import socket
import tkinter as tk
from tkinter import messagebox

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 15000))
def funzione():
    nome = entry_nome.get()
    n_posti = entry_posti.get()
    if not nome or not n_posti or nome.isdigit() or not n_posti.isdigit():
        messagebox.showerror("errore", "Inserisci degli input validi")
        entry_nome.delete(0, tk.END)
        entry_posti.delete(0, tk.END)
        return 
    messaggio = nome + "," + n_posti
    client_socket.sendall(messaggio.encode())
    risposta = client_socket.recv(1024).decode()
    messagebox.showinfo("Risposta server", risposta)
    entry_nome.delete(0, tk.END)
    entry_posti.delete(0, tk.END)

root = tk.Tk()
root.title("Ristorante")

frame = tk.Frame(root, pady = 20, padx = 20)
frame.pack()

label1 = tk.Label(frame, text = "Inserisci il nome")
label1.pack()
entry_nome = tk.Entry(frame, width = 40)
entry_nome.pack(pady = 10)

label2 = tk.Label(frame, text = "Inserisci il numero di posti che vuoi prenotare")
label2.pack()
entry_posti = tk.Entry(frame, width = 40)
entry_posti.pack(pady = 10)

btn = tk.Button(frame, text = "Invia i dati", command = funzione)
btn.pack()

root.mainloop()