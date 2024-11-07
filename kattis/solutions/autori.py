inp = input()
short = ""
names = inp.split('-')
for char in names:
    short += char[0]
print(short)