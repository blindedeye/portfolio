def main() -> None:
    inp = input()
    halloween = "OCT 31"
    christmas = "DEC 25"
    if inp == halloween or inp == christmas:
        print("yup")
    else:
        print("nope")

if __name__ == '__main__':
    main()