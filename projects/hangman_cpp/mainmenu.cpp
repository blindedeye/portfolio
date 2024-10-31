
#include <iostream>
#include <iomanip>
#include "utility.h"
#include "words.h"
#include "game.h"
using namespace std;

void cases(int);
void help();

void mainMenu(){
  clearScreen();
  int menu;

  cout << setfill('#') << setw(32) << "\n"
    << "#      Welcome to Hangman     #\n"
    << setfill('#') << setw(32) << "\n"
    << "# 1. Play Game                #\n"
    << "# 2. Help                     #\n"
    << "# 3. Word List                #\n"
    << "# 4. Add Words                #\n"
    << "# 5. Delete Words             #\n"
    << "# 6. Quit Game                #\n"
    << setfill('#') << setw(32) << "\n";


  cin >> menu;
  cases(menu);
}

void cases(int menu){
  switch(menu){
    case 1:
      game();
      break; // breaks, so that I can call the game from main instead of here. Either way would work, but I wanted to fill main.cpp up a little more!

    case 2:
      help();
      break;

    case 3:
      readFile();
      break;

    case 4:
      writeData();
      break;

    case 5:
      deleteWord();
      break;

    case 6:
      clearScreen();
      exit(3);
  }
}

void help(){
  clearScreen();

  cout << setfill('#') << setw(71) << "\n"
  << "#                       How to Play                                  #\n"
  << setfill('#') << setw(71) << "\n"
  << "#  1) A random word is pulled from the 'Word List'                   #\n"
  << "#  2) _'s will be printed, each indicating a letter in the word.     #\n"
  << "#  3) Type in a letter you guess, and if it is correct, it will      #\n"
  << "#     replace each corresponding _ that contains that letter.        #\n"
  << "#  4) If your letter is not in the word, a part of the stick figure  #\n"
  << "#     will be added to the gallows!                                  #\n"
  << "#  5) If the stick figure is fully hung, you LOSE! If the word is    #\n"
  << "#     guessed before the figure is assembled, you WIN!               #\n"
  << setfill('#') << setw(71) << "\n"
  << "# | Press Enter to return to Main Menu |                             #\n"
  << setfill('#') << setw(71) << "\n";

  cin.ignore(100, '\n');
  cin.get();
  mainMenu();

}
