import socket 
import tkinter as tk
from tkinter import messagebox

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(("127.0.0.1", 12345))
ricevuto = client_socket.recv(1024).decode()
lista_menu = ricevuto.split(",")

def funzione():
    prodotto = variabile.get()
    quantita = entry_quantita.get()
    if not prodotto or not quantita.isdigit():
        messagebox.showerror("errore", "Inserisci input validi")
        entry_quantita.delete(0, tk.END)
        return
    messaggio = prodotto + "," + quantita
    client_socket.sendall(messaggio.encode())
    risposta = client_socket.recv(1024).decode()
    messagebox.showinfo("Risposta del server: ", risposta)
    entry_quantita.delete(0, tk.END)


root = tk.Tk()
root.title("Gestione ristarante")

frame = tk.Frame(root, pady = 20, padx = 20)
frame.pack()

variabile = tk.StringVar(root)
variabile.set(lista_menu[0])

menu = tk.OptionMenu(frame, variabile, *lista_menu)
menu.pack(pady = 15)

label = tk.Label(frame, text = "Inserisci numero di prodotti")
label.pack()
entry_quantita = tk.Entry(frame, width = 40)
entry_quantita.pack(pady = 10)

btn = tk.Button(frame, text = "Invia i dati", command = funzione)
btn.pack(pady = 10)

root.mainloop()

client_socket.close()
