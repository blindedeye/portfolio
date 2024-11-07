/*
Kattis - Hissing Microphone Problem
By: Jake Peterson
Date: 19 October 2022
Hissing Microphone Problem Statement: https://open.kattis.com/problems/hissingmicrophone
Algorithm steps:
1. Read string
2. search for "ss" substring in the string
    - if found, print "hiss"
    - otherwise, print "no hiss"
*/

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

string answer(const string &line);
void testAnswer();
void solve();

int main(int argc, char* argv[]) {
    if (argc == 2 and string(argv[1]) == "test")
        testAnswer();
    else
        solve();
}

string answer(const string &line) {
    string hiss = "ss";
    size_t pos = line.find(hiss);
    if(pos < line.length()){
      return "hiss";
    } else{
      return "no hiss";
    } // FIXME3: FIXED
}

void testAnswer() {
    assert(answer("Whens he comings") == "no hiss");
    assert(answer("he missed the ball") == "hiss"); // FIXME4: FIXED
    cerr << "All test cases passed!\n";
}

void solve() {
    string line;
    getline(cin, line); // FIXME5: FIXED
    cout << answer(line) << endl;
}