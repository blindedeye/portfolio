/*
Sort Two Numbers - Kattis Problem
*/

#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

void program(){
  int n1, n2;
  cin >> n1 >> n2;
  if(n1 > n2){
    cout << n2 << " " << n1;
  }
  else{
    cout << n1 << " " << n2;
  }


}

int main(){
  program();
  return 0;
}