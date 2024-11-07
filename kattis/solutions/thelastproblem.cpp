/*
Kattis - The Last Problem
User-defined functions and Library Functions Lab
Updated By: Jake Peterson
CSCI 111
Date: 09-16-2022
Read and solve The Last Problem: https://open.kattis.com/problems/thelastproblem

Algorithm:
        1. Read the input string
        3. Create the output as asked and print it
*/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
using namespace std;

string twilight(const string&);
string readData();

int main(){

  string input = "input";

  input = readData();
  // FixMe 1 Call twilight function passing input as an argument
  // Store the returned result into answer Variable
  input = twilight(input);

  string answer = input;
  //print answer
  printf("%s\n", answer.c_str());
  return 0;

}

  string readData() {
    string input;
    getline(cin,input);
    return input;
  }

  string twilight(const string& input) {
    string ans = "Thank you, " + input + ", and farewell!";
    return ans;
  }