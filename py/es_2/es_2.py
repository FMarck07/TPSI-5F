'''
2) Statistiche su una sequenza di numeri
Scrivi un programma che chieda all’utente di inserire una lista di numeri interi.
Usa funzioni e cicli per:
● calcolare la media dei numeri
● contare quanti numeri sono sopra la media e quanti sotto
● creare una nuova lista contenente solo i numeri maggiori della media
● determinare la lunghezza della sequenza più lunga di numeri consecutivi uguali
'''

def calcola_media(numeri):
    return sum(numeri) / len(numeri)

def sequenza_massima(numeri):
    max_seq = 1
    seq_attuale = 1

    for i in range(1, len(numeri)):
        if numeri[i] == numeri[i-1]:
            seq_attuale += 1
            if seq_attuale > max_seq:
                max_seq = seq_attuale
        else:
            seq_attuale = 1

    return max_seq


numeri = []

n = int(input("Quanti numeri vuoi inserire: "))

for i in range(n):
    numero = int(input("Inserisci numero: "))
    numeri.append(numero)

media = calcola_media(numeri)
print("Media =", media)

sopra = 0
sotto = 0
maggiori_media = []

for num in numeri:
    if num > media:
        sopra += 1
        maggiori_media.append(num)
    elif num < media:
        sotto += 1

print("Numeri sopra la media:", sopra)
print("Numeri sotto la media:", sotto)
print("Lista numeri maggiori della media:", maggiori_media)
print("Sequenza massima consecutiva:", sequenza_massima(numeri))




