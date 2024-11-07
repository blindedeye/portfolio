/*
Kattis - Simon Says
By: Jake Peterson
Date: 18 October 2022
Hissing Microphone Problem Statement: https://open.kattis.com/problems/simonsays
Algorithm steps:
1. Read N
2. Loop N times:
  i. Read a line
  ii. If the line starts with "Simon says",
    print the rest of the string. Note: print the leading space after says as well!
  3. Otherwise, skip the line
*/

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

string answer(const string &line);
void testAnswer();
void solve();

int main(int argc, char* argv[]) {
  if (argc == 2 and string(argv[1]) == "test") {
    testAnswer(); //FIXME1: FIXED
  }
  else
    solve();
}

string answer(const string &line) {
  string simon = "Simon says";
  if(line.rfind(simon, 0) == 0){
    return line.substr(11);
  } else{// FIXME2: FIXED
  return "";
  }
}

void testAnswer() {
  string ans = answer("Simon says laugh!");

  cerr << "ans = " << ans << endl;
  assert(ans == "laugh!");
  assert(answer("Write more programs.") == "");
  assert(answer("Simon says Hello World!") == "Hello World!");
  assert(answer("Woah, calm down bro o.O") == ""); // FIXME3: FIXED
  cerr << "All test cases passed!\n";
}

void solve() {
  string ans, line;
  int N;
  cin >> N;
  cin.ignore(80, '\n'); //FIXME4 : FIXED
  while (N--) {
    getline(cin, line); //FIXME5: FIXED
    ans = answer(line); //FIXME6: FIXED
    cout << ans << endl;//FIXME7: FIXED
    if (ans == "") continue;
  }
}