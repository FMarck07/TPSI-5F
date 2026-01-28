'''
1) lista di studenti
Scrivi un programma che gestisca i dati di una classe.
L’utente inserisce per ogni studente: nome e una lista di voti (numeri interi da 1 a 10).
Il programma deve:
● salvare i dati in una lista di liste (o lista di dizionari)
● usare una funzione per calcolare la media dei voti di ogni studente
● usare un ciclo per determinare:
○ lo studente con la media più alta
○ lo studente con la media più bassa
● creare una nuova lista con i nomi degli studenti promossi (media ≥ 6)
● stampare un riepilogo finale con nome, media e stato (promosso / bocciato)
'''

# funzione per calcolare la media
def media(voti):
    return sum(voti) / len(voti)

studenti = []

n = int(input("Numero studenti: "))
# inserimento dati
for i in range(n):
    nome = input("Nome: ")
    voti = []
    num_voti = int(input("Inserisci numero di voti dello studente: "))

    for j in range(num_voti):  # 3 voti fissi (più semplice)
        voto = int(input("Voto: "))
        voti.append(voto)

    studenti.append({"nome": nome, "voti": voti})

# inizializzazioni
media_max = 0
media_min = 10
migliore = ""
peggiore = ""
promossi = []

# elaborazione
for s in studenti:
    m = media(s["voti"])

    if m > media_max:
        media_max = m
        migliore = s["nome"]

    if m < media_min:
        media_min = m
        peggiore = s["nome"]

    if m >= 6:
        promossi.append(s["nome"])

# stampa finale
print("\nRISULTATI")
for s in studenti:
    m = media(s["voti"])
    stato = "Promosso" if m >= 6 else "Bocciato"
    print(s["nome"], "- media:", m, "-", stato)

print("Media più alta:", migliore)
print("Media più bassa:", peggiore)
print("Promossi:", promossi)

