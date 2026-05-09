import socket
import tkinter as tk
from tkinter import messagebox, ttk

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 12345))

valute = ["EUR", "USD", "GBP", "JPY", "CHF"]

def invia():
    orig = combo_orig.get()
    dest = combo_dest.get()
    imp = entry_imp.get()
    if not orig or not dest or not imp:
        messagebox.showerror("Errore", "Inserisci tutti i dati")
        return
    try:
        importo = float(imp)
        if importo <= 0:
            raise ValueError
    except ValueError:
        messagebox.showerror("Errore", "Importo deve essere > 0")
        return
    messaggio = f"{orig},{dest},{importo}"
    client.sendall(messaggio.encode())
    risposta = client.recv(1024).decode()
    messagebox.showinfo("Risultato", risposta)

root = tk.Tk()
root.title("Convertitore Valute")
root.geometry("400x300")

frame = tk.Frame(root, padx=20, pady=20)
frame.pack()

tk.Label(frame, text="Da valuta:").pack(anchor="w")
combo_orig = ttk.Combobox(frame, values=valute, state="readonly")
combo_orig.pack(fill="x", pady=5)

tk.Label(frame, text="A valuta:").pack(anchor="w")
combo_dest = ttk.Combobox(frame, values=valute, state="readonly")
combo_dest.pack(fill="x", pady=5)

tk.Label(frame, text="Importo:").pack(anchor="w")
entry_imp = tk.Entry(frame)
entry_imp.pack(fill="x", pady=5)

btn = tk.Button(frame, text="Converti", command=invia)
btn.pack(pady=20)

root.mainloop()
client.close()
