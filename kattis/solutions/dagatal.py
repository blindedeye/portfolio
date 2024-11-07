def days(month: int) -> int:
    if month == 2:
        return 28
    elif month == 4 or month == 6 or month == 9 or month == 11:
        return 30
    else:
        return 31

inp = input()
print(days(int(inp)))