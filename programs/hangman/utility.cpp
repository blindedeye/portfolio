
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("clS");
    #else
        system("clear");
    #endif
}

string getRandWord(){
  ifstream fin;
  string wordBank = "words.txt";
  string checkWords, temp;
  int lines = 0;
  fin.open(wordBank, fin.in);

  while(getline(fin, checkWords)){
    lines++;
  }
  fin.close();
  fin.open(wordBank);
  //cout << lines << endl;
  string words[lines];
  for(int i = 0; i < lines; i++){
    getline(fin, temp);
    words[i] = temp;
    //cout << words[i] << " ";
  }
  fin.close();

  srand(time(0));
  int randWord = rand() % lines;
  //cout << randWord << endl;
  string currentWord = words[randWord];
  //cout << currentWord << endl;
  return currentWord;
}
