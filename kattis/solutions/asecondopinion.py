def main() -> None:
    ns = int(input())
    modh = ns % 3600
    nh = round((ns - modh) / 3600)
    modm = modh % 60
    nm = round((modh - modm) / 60)
    ns = modm
    print(f"{nh} : {nm} : {ns}")

if __name__ == '__main__':
    main()