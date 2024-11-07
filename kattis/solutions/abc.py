def main() -> None:
    temp_a, temp_b, temp_c = map(int, input().split())
    order = input()
    if temp_a > 100 or temp_b > 100 or temp_c > 100:
        quit()
    nums = sorted([temp_a, temp_b, temp_c])
    a, b, c = nums[0], nums[1], nums[2]
    out = []
    for char in order:
        if char == 'A':
            out.append(a)
        elif char == 'B':
            out.append(b)
        else:
            out.append(c)
    print(*out)

if __name__ == '__main__':
    main()