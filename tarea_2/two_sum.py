"""Solucion al problema suma de dos usando un diccionario."""

print("Tarea 2 ELO320 2026-1")
a = [2, 11, 15, 45, 9, 7, 123]
target = 9

d = {}
for i in range(len(a)):
    needed = target - a[i]
    if needed in d:
        print(i, d[needed])
        break
    d[a[i]] = i
