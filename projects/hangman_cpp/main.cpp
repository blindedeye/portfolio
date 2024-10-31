/*
Hangman Final Project
Written By: Jake Peterson
Date: 08 Dec 2022

Program is a simple game of hangman, where a user inputs letters to try and guess a randomly generated word from a list of words.

Citations:
https://cplusplus.com/reference/cstdlib/srand/
Basnet Jupyter Notebook References
*/

// Library Headers
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
// My own Headers
#include "utility.h"
#include "stages.h"
#include "mainmenu.h"
#include "game.h"

using namespace std;

int main(){
  mainMenu();
  game();
}

