/*
Main chunk of the game -> all logic
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include "utility.h"
#include "stages.h"
#include "mainmenu.h"

using namespace std;

void game();
bool checkGuess(char[], char, int*);
void readData();
void callGuess(char[], char[], char[], int, int*, string);
bool checkWin(char*, char[], int, string);
string convertToString(char[], int);

void game(){
  clearScreen();
  int tries = 6; // permitted amount of tries
  int val = -1; // How many times you have guessed (including right guesses)
  char guess[26];
  string word = getRandWord();
  int wordLength = word.length();
  char wordArr[wordLength];
  strcpy(wordArr, word.c_str()); // making rand word into array to check pos and char's in word
  //cout << wordArr[0] << " + " << wordArr[3]; //for testing purpose
  char wordMap[wordLength];
  //cout << word << endl; // testing purpose

  for(int i=0; i<wordLength; i++){
    wordMap[i] = '_';
  }

  while(tries > 0 && tries <= 6){
    switch(tries){
      case 6:{
        defaultStage();
        callGuess(guess, wordMap, wordArr, wordLength, &val, word);
        tries--;
        break;
      }
      case 5:{
        clearScreen();
        stage1();
        callGuess(guess, wordMap, wordArr, wordLength, &val, word);
        tries--;
        break;
      }
      case 4:{
        clearScreen();
        stage2();
        callGuess(guess, wordMap, wordArr, wordLength, &val, word);
        tries--;
        break;
      }
      case 3:{
        clearScreen();
        stage3();
        callGuess(guess, wordMap, wordArr, wordLength, &val, word);
        tries--;
        break;
      }
      case 2:{
        clearScreen();
        stage4();
        callGuess(guess, wordMap, wordArr, wordLength, &val, word);
        tries--;
        break;
      }
      case 1:{
        clearScreen();
        stage5();
        cout << "Game OVER!!! HAHAHA, YOU LOST!!!" << endl
             << "The word was: " << word << endl 
             << "--> Enter to Return to Main Menu <--\n";

        cin.ignore(100, '\n');
        cin.get();
        mainMenu();
        tries = 1000;
        break;
      }
    }
  }
  
}

bool checkGuess(char guess[], char tempGuess, int* val){
  for(int i=0; i<26; i++){
    if(tempGuess == guess[i]){
      cout << "Already guessed (" << tempGuess << ")! Please guess again: ";
      return false;
      break;
    }
  }
  *val = *val + 1;
  //cout << *val; // testing purpose
  guess[*val] = tempGuess;
  return true;
}

void callGuess(char guess[], char wordMap[], char wordArr[], int wordLength, int* val, string word){
  char tempGuess;
  string tempGuessString;
  bool cont = true;

  do{
    bool guessed = false;
    for(int i = 0; i < wordLength; i++){
      cout << " " << wordMap[i];
   }
    cout << "\n\n" << "Guess Letter: ";
    cin >> tempGuessString;
   
    while(tempGuessString.length() > 1 || checkGuess(guess, tempGuessString[0], val) == false){
      if (tempGuessString.length() > 1) // Checks if you entered more than 1 character: ie. abc will make this condition true
        cout << "You entered too many characters! Try again: ";
      cin >> tempGuessString;
  }
  tempGuess = tempGuessString[0]; 
  for(int i=0; i<wordLength; i++){
    if(tempGuess == wordArr[i]){  // if guess = a letter in the array of word to guess
      wordMap[i] = tempGuess; // _ is replaced with guessed letter
      //cout << wordMap[i] << " and " << wordArr[i]; // for testing
      checkWin(wordMap, wordArr, wordLength, word);
      guessed = true;
    }
  }
  if(guessed == false){
    break;
  }
  } while(cont == true);
}

bool checkWin(char wordMap[], char wordArr[], int wordLength, string word){
  string checkS = convertToString(wordMap, wordLength);
  if(checkS == word){ // if wordMap converted to string = word to guess, then win
    cout 
    << "        CONGRATS!!! YOU WIN!!!!" << endl
    << "      The word was: " << word << endl
    << "--> Press Enter to Return to Main Menu <--\n";
        cin.ignore(100, '\n');
        cin.get();
        mainMenu();
    return true;
  } // else continue / didn't win
  return false;
}

string convertToString(char wordMap[], int wordLength){
  string s = "";
  for (int i = 0; i < wordLength; i++) {
    s = s + wordMap[i];
  }
    return s;
}