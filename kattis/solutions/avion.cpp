/*
Updated by: Jake Peterson
Date: 25 October 2022
Avion Kattis Assignment
*/
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

void unitTest();
bool isFbi(string line);
void solve();

int main(int argc, char* argv[]) {
    solve();
}

bool isFbi(string line){
  if(line.find("FBI") != -1){
    return true;
  } else{
    return false;
  }
}

void solve(){
  int a1, a2, a3, a4, a5;
  string line;
  bool isPrinted = false;

  for(int i = 1; i <= 5; i++){
    cin >> line;
    if(isFbi(line)){
      isPrinted = true;
      cout << i << " ";
    }
  }
    if(!isPrinted) {
      cout << "HE GOT AWAY!";
     }
}