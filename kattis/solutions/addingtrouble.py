def check(a: int, b: int, c: int) -> int:
    if a + b == c:
        return 'correct!'
    else:
        return 'wrong!'

inp = input()
a, b, c = inp.split()
print(check(int(a), int(b), int(c)))