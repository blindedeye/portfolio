def answer(a: str, b: str) -> str:
    """
    Sort function
    """
    if int(a) > int(b):
        print(f"{b} {a}")
        ans = f"{b} {a}"
    else:
        print(f"{a} {b}")
        ans = f"{a} {b}"
    return ans


def main() -> None:
    """Entry point"""
    line = input()
    a, b = line.split()
    answer(a, b)


if __name__ == '__main__':
    main()