/*
Kattis - Stuck In A Time Loop
Loop Lab
Updated By: Jake Peterson
CSCI 111
Date: 18 October 2022
Read and solve the Kattis problem: https://open.kattis.com/problems/timeloop
Algorithm Steps:
  1. Using a function, read and return N
  2. Declare a dynamic variable to store, N returned by function in 1.
  3. Define a function to get the necessary spell given N
  4. Define a function to print answer
    4.i Within the function, use a loop to call spell function to print spell N times:
      1 Abracadabra
      2 Abracadabra
      ...
      N Abracadabra
*/

#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>
#include <cmath>
#include <sstream>
using namespace std;


using pos_int = unsigned short;

string spell(const pos_int);

void testSpell();

void printAnswer(const pos_int);

pos_int readNumber();

int main(int argc, char* argv[]) {
  if (argc == 2 and string(argv[1]) == string("test")) {
    // FIXME1: FIXED
    testSpell();
    return 0;
  }

  pos_int *N = new pos_int;
  //FIXME2: FIXED
  //FIXME3: FIXED
  *N = readNumber();
  printAnswer(*N);
}

pos_int readNumber() {
  //FIXME4: FIXED
  pos_int *N = new pos_int;
  cin >> *N;
  return *N;
  return 0;
}

string spell(pos_int n) {
  return to_string(n) + " Abracadabra";
}

void testSpell() {
  pos_int * n = new pos_int;
  *n = 10;
  assert(spell(*n) == "10 Abracadabra");
  // FIXME5: FIXED
  cerr << "Yay... all test cases passed!\n";
}

void printAnswer(const pos_int N) {
  for(pos_int i=1; i<=N; i++) {
    printf("%s\n", spell(i).c_str());
  }
}