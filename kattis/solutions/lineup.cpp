/*
line them up
By: Jake Peterson
Date: 11/1/22
CSCI111

Program to check if an array of names is in order.
*/

#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <iterator>


using namespace std;

string solve();

int main(int argc, char* argv[]){
    cout << solve() << endl;
}

string solve(){
    int n;
    cin >> n;
    int range = n;
    string names[n];
    for (int i = 0; i < n; i++){
      cin >> names[i];
    }
    if (is_sorted(names, names + n)){
      return "INCREASING";
    }
    if(is_sorted(names, names + n, greater<string>())){
      return "DECREASING";
    }
    else{
      return "NEITHER";
      }
}