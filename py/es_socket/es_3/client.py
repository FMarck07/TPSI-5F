import socket
import tkinter as tk
from tkinter import messagebox
from datetime import datetime

# Connessione al server
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 12345))

nGiorni = 0
giorno_corrente = 0
daysData = []

def getNumDays():
    global nGiorni
    try:
        nGiorni = int(entry.get())
        if nGiorni <= 0:
            raise ValueError
    except ValueError:
        messagebox.showerror("Errore", "Inserisci un numero valido di giorni")
        return

    start_window.destroy()
    root.deiconify()
    aggiorna_titolo()

def aggiorna_titolo():
    label_title.config(
        text=f"Inserimento dati giorno {giorno_corrente + 1} di {nGiorni}"
    )

def mainInterfaceLogic():
    global giorno_corrente

    giorno = entry1.get()

    try:
        datetime.strptime(giorno, "%d/%m/%Y")
    except ValueError:
        messagebox.showerror("Errore", "Formato data non valido (GG/MM/AAAA)")
        return

    try:
        temp12 = int(entry2.get())
        temp24 = int(entry3.get())
    except ValueError:
        messagebox.showerror("Errore", "Le temperature devono essere numeriche")
        return

    message = f"{giorno}|{temp12}|{temp24}"
    daysData.append(message)

    giorno_corrente += 1
    pulisci_campi()

    if giorno_corrente == nGiorni:
        invia_dati()
    else:
        aggiorna_titolo()

def pulisci_campi():
    entry1.delete(0, tk.END)
    entry2.delete(0, tk.END)
    entry3.delete(0, tk.END)

def invia_dati():
    for dato in daysData:
        client_socket.sendall((dato + "\n").encode())
        risposta = client_socket.recv(1024).decode()
        messagebox.showinfo("Risposta dal Server", risposta)

    client_socket.close()
    root.destroy()

# GUI

root = tk.Tk()
root.withdraw()

start_window = tk.Toplevel(root)
start_window.title("Stazione Meteo")
tk.Label(start_window, text="Quanti giorni vuoi inserire?").pack(pady=5)
entry = tk.Entry(start_window)
entry.pack(pady=5)
tk.Button(start_window, text="Conferma", command=getNumDays).pack(pady=10)
start_window.geometry("400x120")

root.geometry("400x300")
label_title = tk.Label(root, text="")
label_title.pack(pady=5)

tk.Label(root, text="Giorno (GG/MM/AAAA)").pack()
entry1 = tk.Entry(root)
entry1.pack()

tk.Label(root, text="Temperatura ore 12").pack()
entry2 = tk.Entry(root)
entry2.pack()

tk.Label(root, text="Temperatura ore 24").pack()
entry3 = tk.Entry(root)
entry3.pack()

tk.Button(root, text="Invia dati", command=mainInterfaceLogic).pack(pady=10)

root.mainloop()
