import sys

i = 1
while True:
    try:
        line = input().split()
        if len(line) == 0:
            break
        n = int(line[0])
        numbers = [int(x) for x in line[1:]]

        min_val = min(numbers)
        max_val = max(numbers)
        range_val = max_val - min_val

        print(f"Case {i}: {min_val} {max_val} {range_val}")
        i += 1
    except EOFError:
        break