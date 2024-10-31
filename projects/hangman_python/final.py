#--------------------------------------------------------------------------------------------------------------------------#
# Author: Jake Peterson
# Description:
# Note: For unit testing, run the argument 'test' during compiling. For example: 'python3 final.py test' Also, I used the 
#       assert method as I am more familiar with it (from when I took CS1). As well as our textbook says it's an option: 
#       "There is a built-in Python statement called assert that does almost the same as our test function."
# References: https://www.geeksforgeeks.org/switch-case-in-python-replacement/ <- switch
#             https://www.geeksforgeeks.org/pad-or-fill-a-string-by-a-variable-in-python-using-f-string/  <- f strings
#             https://www.geeksforgeeks.org/clear-screen-python/ <- Clearing Screen using os library
#             https://docs.python.org/3/library/random.html <- random library
#             https://docs.python.org/3/library/sys.html <- additional arguments during compilation
#--------------------------------------------------------------------------------------------------------------------------#
import string
import os
import random
import sys

# Function to clear the screen
def clear():
    os.system("clear")

# Function to load the ASCII stage
def loadStage(stage):
    src="stages/stage"
    fin=open(src+str(stage)+".txt","r")
    lines=fin.readlines()
    fin.close()
    for line in lines:
        print(line)

# Function to pull a 'random' word from words.txt
def pickWord(src):
    fin=open(src,"r")
    words=fin.readlines()
    fin.close()
    fileLength=len(words)
    wordInt=random.randint(0,fileLength-1)
    return words[wordInt].strip()

# Function to print the guessed letters
def guessedBox(letters):
    print("Guessed letters: ")
    for i in letters:
        print(f"{i} ",end='')
    print("\n")
    return letters
        
# Function to print each underscore for the word
def printUnders(word,guessedLets):
    unders=[]
    for letter in word:
        if letter in guessedLets:
            unders.append(letter)
        else:
            unders.append('_')
    print(" ".join(unders))
    return " ".join(unders)

# Function to check if the word is solved
def checkWin(unders):
    if "_" not in unders:
        return True
    else:
        return False

# Main game loop
def game():
    stage=0
    tries=6
    unders=[]
    alphabet="abcdefghijklmnopqrstuvwxyz"
    guessedLets=[]
    guessedBox(guessedLets)
    loadStage(stage)
    word=pickWord("words.txt")
    printUnders(word,guessedLets)

    while stage<tries:
        guess=str(input("Guess a letter > ")).lower()
        if len(guess)!=1:
            print(f"'{guess}' is too long! Please enter one letter at a time!")
            continue
        elif guess not in alphabet:
            print(f"'{guess}' is not a letter! Please enter a letter!")
            continue
        elif guess in guessedLets:
            print(f"The letter '{guess}' has already been guessed!")
            continue
        elif guess not in guessedLets and guess not in word:
            guessedLets.append(guess)
            stage+=1
            clear()
            guessedBox(guessedLets)
            loadStage(stage)
            unders=printUnders(word,guessedLets)
        elif guess in word:
            guessedLets.append(guess)
            clear()
            guessedBox(guessedLets)
            loadStage(stage)
            unders=printUnders(word,guessedLets)
            if checkWin(unders) is True:
                print(f"Congratulations! You guessed the word!")
                input("Press Enter to continue...")
                menu()
    print(f"Game Over! You lost, the word was {word}!")
    input("Press Enter to continue...")
    clear()
    menu()

# Function to add a word to the word list
def addWord():
    clear()
    fout=open("words.txt","a")
    yn=input("Would you like to add a word? (y/n) > ").lower()
    if yn=="y":
        word=input("What word would you like to add? > ")
        fout.write(word+"\n")
        fout.close()
        addWord()
    else:
        fout.close()
        wordsMenu()

# Function to remove a word from the word list
def removeWord():
    clear()
    fin=open("words.txt","r")
    words=fin.readlines()
    fin.close()
    yn=input("Would you like to remove a word? (y/n) > ").lower()
    if yn=="y":
        word=input("What word would you like to remove? > ").strip() + "\n"
        if word in words:
            words.remove(word)
            fout=open("words.txt","w")
            fout.writelines(words)
            fout.close()
            removeWord()
        else:
            wordsMenu()
    

# Function to print the words in the list
def listWords():
    clear()
    fin=open("words.txt","r")
    words=fin.readlines()
    fin.close()
    for word in words:
        print(word.strip())
    input("\nWord List\nPress Enter to continue...")
    wordsMenu()

# Function to print the word menu
def wordsMenu():
    clear()
    print(f"{'':#<18}\nWord Settings\n{'':#<18}\n1. Add a Word\n2. Remove a Word\n3. Word List\n4. Main Menu\n{'':#<18}\n")
    arg=int(input(""))
    match arg:
        case 1:
            addWord()
        case 2:
            removeWord()
        case 3:
            listWords()
        case 4:
            menu()

# Function to print the main menu
def menu():
    clear()
    print(f"{'':#<15}\nHangman Game\n{'':#<15}\n1. Play\n2. Words\n3. Exit Game\n{'':#<15}\n")
    arg=int(input(""))
    clear()
    match arg:
        case 1:
            game()
        case 2:
            wordsMenu()
        case 3:
            quit()

# Function to unit test various functions of the game
def unitTest():
    # pickWord() Unit Test
    assert pickWord("testFiles/test0.txt")=="secret"
    assert pickWord("testFiles/test1.txt")=="anakin"

    # guessedBox() Unit Test
    assert guessedBox("a")=="a","Wrong letter(s) returned"
    assert guessedBox(["a","b","c"])==["a","b","c"],"Wrong letter(s) returned"

    # printUnders() Unit Test
    assert printUnders("python",["p","t","n"])=="p _ t _ _ n","Wrong output"
    assert printUnders("hangman",["h","a","n","g"])=="h a n g _ a n","Wrong output"

    # checkWin() Unit Test
    assert checkWin("j _ k _")==False,"False Win given"
    assert checkWin("s u c k e r")==True,"Real Win not detected"

    clear()
    print("(Unit Test): All test cases passed!\n")

if __name__ == "__main__":
    if "test" in sys.argv:
        clear()
        unitTest()
    else:
        clear()
        menu()