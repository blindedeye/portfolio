/*
A New Alphabet Kattis Problem
Written by: Jake Peterson
Date: 06 Dec 2022

Program uses a map to convert line of input into the same line, but translated into the new alphabet
*/
#include <iostream>
#include <string>
#include <map>
#include <cassert>

using namespace std;

map<char, string> alphabet = {
    {'a', "@"}, {'b', "8"}, {'c', "("}, {'d', "|)"}, {'e', "3"}, {'f', "#"}, {'g', "6"}, {'h', "[-]"}, 
    {'i', "|"}, {'j', "_|"}, {'k', "|<"}, {'l', "1"}, {'m', "[]\\/[]"}, {'n', "[]\\[]"}, {'o', "0"}, 
    {'p', "|D"}, {'q', "(,)"}, {'r', "|Z"}, {'s', "$"}, {'t', "']['"}, {'u', "|_|"}, {'v', "\\/"}, 
    {'w', "\\/\\/"}, {'x', "}{"}, {'y', "`/"}, {'z', "2"}
};

void solve();
string convertToAlpha(string);
void unitTest();

int main(int argc, char* argv[]){
    if(argc == 2 and string(argv[1]) == "test")
        unitTest();
    else
        solve();
        return 0;
}

void solve(){
    string input, trans;
    getline(cin, input);
    trans = convertToAlpha(input);
    cout << trans << endl;

}

string convertToAlpha(string phrase){
    string trans = "";
    for(char c : phrase){
        c = char(tolower(c));
        if(alphabet.count(c) == 1){
        trans += alphabet.at(c);
        } else{
            trans += c;
        }
    }
    return trans;
}

void unitTest(){
    string phrase = "jake";
    assert(convertToAlpha(phrase) == "_|@|<3");

    phrase = "Computer Science";
    assert(convertToAlpha(phrase) == "(0[]\\/[]|D|_|']['3|Z $(|3[]\\[](3");

    phrase = "cranIal SePtUm";
    assert(convertToAlpha(phrase) == "(|Z@[]\\[]|@1 $3|D']['|_|[]\\/[]");

    phrase = "These are not the droids you are looking for.";
    assert(convertToAlpha(phrase) == "']['[-]3$3 @|Z3 []\\[]0'][' ']['[-]3 |)|Z0||)$ `/0|_| @|Z3 100|<|[]\\[]6 #0|Z.");

    cerr << "All test cases passed!\n";
}