#pragma once
using namespace std;

void game();
bool checkGuess(char[], char, int*);
void readData();
void callGuess(char[], char[], char[], int, int*, string);
bool checkWin(char*, char[], int, string);
string convertToString(char[], int);