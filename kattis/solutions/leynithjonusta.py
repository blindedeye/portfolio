def main() -> None:
    inp = input()
    out_list = []
    for char in inp:
        if char != ' ':
            out_list.append(char)
    out = ''.join(out_list)
    print(out)

if __name__ == '__main__':
    main()