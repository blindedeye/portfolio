#include <iostream>
#include "utility.h"
#include "mainmenu.h"
#include <fstream>
#include <iomanip>

using namespace std;

void readFile(){
  string file_path = "words.txt";
  fstream file;
  file.open(file_path, file.in | file.binary | file.ate);

  if (!file.is_open())
    cout << "failed to open " << file_path << '\n';
    else {
    size_t size = file.tellg();
    file.seekg(0, file.beg);

    char * buffer = new char[size];
    if (file.read(buffer, size))
    {
      cout << "Word List:\n"
      << buffer
      << "| Press Enter to go back to Main Menu! |\n";

    }
    delete[] buffer;
}
  file.close();
  cin.ignore(100, '\n');
  cin.get();
  mainMenu();

}

void writeData(){
    clearScreen();
    ofstream fout;
    ifstream fin;

    string insWord;
    string word;
    bool inBank = false;
    char yn = 'y';

    while(yn == 'y' || yn == 'Y'){
      fin.open("words.txt");
      fout.open("words.txt", fout.out | fout.app | fout.ate);

      if(!fout.is_open()){
        cout << "failed to open words.txt\n";
        mainMenu();

      } else {
      cout << "Enter Word to Add: ";
      cin >> insWord;

      while(getline(fin, word)){
        if(word == insWord){
          cout << "Word is already in the bank!\n";
          inBank = true;
      }
    }
      if(inBank != true){
        fout << insWord << endl;
        cout << "Word Successfully added to word bank! Would you like to add another word? (y/n): ";
        cin >> yn;
      } else{
      cout << "Would you like to add a different word? (y/n): ";
      cin >> yn;
  }
      fout.close();
      fin.close();
  }

    clearScreen();
  }
    mainMenu();
}


void deleteWord(){
  char yn;
  string delWord;
  string word;

  ifstream fin;
  ofstream fout;
  fin.open("words.txt");
  fout.open("temp.txt");

  do{
    clearScreen();
    cout << "Enter Word to be Removed: ";
    cin >> delWord;

    while(getline(fin, word)){
      if(word != delWord)
        fout << word << endl;
      }
    remove("words.txt");
    rename("temp.txt", "words.txt");
    fin.close();
    fout.close();

  cout << "Would you like to delete another word? (y/n): ";
  cin >> yn;
} while(yn == 'y' || yn == 'Y');
  mainMenu();
}
