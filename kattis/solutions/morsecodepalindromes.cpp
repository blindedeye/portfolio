/*
Map Lab
Kattis - Morse Code Palindromes
Updated By: Jake Peterson
Date: 04 Dec 2022
Solution to Morse Code Palindromes Problem: https://open.kattis.com/problems/morsecodepalindromes
Algorithm steps:
1. Creae a map of char to morse code
2. Read in a string
3. Convert the string to morse code
   i. for each char in string, find its morse code in map
   ii. append morse code to a string if char key is found
4. Check if morse code is a palindrome
  i. compare first and last char
  ii. if they are the same, compare second and second last char
  iii. if they are the same, compare third and third last char
  iv. repeat until all chars are compared until mid index or a mismatch is found
5. Print 1 if morse code is a palindrome, 0 otherwise
*/

#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <string>
#include <cstring>

using namespace std;

map<char, string> morseCode = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."},
    {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},
    {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"},
    {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
    {'8', "---.."}, {'9', "----."}, 
};

string convertToMorse(const string&);
bool isPalindrome(const string&);
void testConvertToMorse();
void testIsPalindrome();
void solve();
void unittest();

int main(int argc, char* argv[]) {
    if (argc == 2 and string(argv[1]) == "test")
        unittest();
    else
        solve();
}

void solve() {
    string phrase, morse;
    // FIXME1 - FIXED
    getline(cin, phrase); // have to use getline not cin to ignore space

    // FIXME2 - FIXED
    morse = convertToMorse(phrase);

    if(isPalindrome(morse) == true){
        cout << "1\n";
    } else{
        cout << "0\n";
    } // FIXME3 and FIXME4 - FIXED
}

string convertToMorse(const string& phrase) {
    string morse = "";
    // convert phrase to morse code
    // for each char in phrase, convert char to uppercase, find its morse code in morseCode map
    // append morse code to a string if char key is found
    for (char c : phrase) {
        c = char(toupper(c));
        if(morseCode.count(c) == 1){
            morse += morseCode.at(c);
    } // FIXME5 - FIXED
}
    return morse;
}

bool isPalindrome(const string& morse) {
    string reverse = "";
    
    if(morse.empty()){
        return false;
    }else{

    for(auto ch = morse.rbegin(); ch != morse.rend(); ch++){
            reverse.push_back(*ch);
        }
    if(morse == reverse){
        return true;
    } else {
        return false;
    }
    // FIXME6 - FIXED
}
}


void testConvertToMorse() {
    assert(convertToMorse("A") == ".-");
    assert(convertToMorse("9") == "----.");
    assert(convertToMorse("Aa") == ".-.-");
    cerr << convertToMorse("AaBb") << endl;
    assert(convertToMorse("AaBb") == ".-.--...-...");
    assert(convertToMorse("Race car!") == ".-..--.-..-.-..-.-.");
    assert(convertToMorse("1881") == ".-------..---...----");
    // FIXME7 - FIXED

    assert(convertToMorse("Jake") == ".---.--.-.");
    assert(convertToMorse("app") == ".-.--..--.");
    assert(convertToMorse("bb") == "-...-...");
}

void testIsPalindrome() {
    string morse = convertToMorse("A");
    assert(isPalindrome(morse) == false);
    morse = convertToMorse("AaBb");
    assert(isPalindrome(morse) == false);
    morse = convertToMorse("Race car!");
    assert(isPalindrome(morse) == false);
    morse = convertToMorse("1881");
    assert(isPalindrome(morse) == false);
    // FIXME8 - FIXED

    morse = convertToMorse("jake");
    assert(isPalindrome(morse) == false);
    morse = convertToMorse("duds");
    assert(isPalindrome(morse) == false);
    morse = convertToMorse("e");
    assert(isPalindrome(morse) == true);

}

void unittest() {
  // FIXME9 - FIXED
  testConvertToMorse();
  testIsPalindrome();
  cerr << "All unittests passed!\n";
}