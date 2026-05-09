import socket
import tkinter as tk
from tkinter import messagebox

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(("127.0.0.1", 12345))
# Riceve la lista dei tipi utente dal server
ricevuto = client_socket.recv(1024).decode()
lista_tipi = ricevuto.split(",")

def start_client():
    tipo = variabile.get()
    kwh = entry_kwh.get()

    if not tipo or not kwh:
        messagebox.showerror("Errore", "Inserisci tutti i dati")
        entry_kwh.delete(0, tk.END)
        return
    try:
        kwh_val = float(kwh)
        if kwh_val <= 0:
            raise ValueError
    except ValueError:
        messagebox.showerror("Errore", "I kWh devono essere un numero > 0")
        entry_kwh.delete(0, tk.END)
        return

    messaggio = f"{tipo},{kwh_val}"
    client_socket.sendall(messaggio.encode())
    risposta = client_socket.recv(1024).decode()
    messagebox.showinfo("Risultato bolletta", risposta)
    entry_kwh.delete(0, tk.END)

root = tk.Tk()
root.title("Calcolo Bolletta Elettrica")

frame = tk.Frame(root, pady=20, padx=20)
frame.pack()

variabile = tk.StringVar(root)
variabile.set(lista_tipi[0])  # primo tipo come default

menu = tk.OptionMenu(frame, variabile, *lista_tipi)
menu.pack(pady=15)

label = tk.Label(frame, text="Inserisci i kWh consumati")
label.pack(pady=10)
entry_kwh = tk.Entry(frame, width=40)
entry_kwh.pack(pady=10)

btn = tk.Button(frame, text="Calcola bolletta", command=start_client)
btn.pack(pady=10)

root.mainloop()
client_socket.close()
