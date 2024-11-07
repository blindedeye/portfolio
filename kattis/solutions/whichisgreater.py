def greater(a: int, b: int) -> int:
    if a > b:
        return 1
    else:
        return 0

inp = input()
a, b = inp.split()
print(greater(int(a), int(b)))