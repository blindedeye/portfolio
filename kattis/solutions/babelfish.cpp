/*
Kattis Babelfish
Written by: Jake Peterson
Date: 06 Dec 2022

https://en.cppreference.com/w/cpp/container/map/
https://cplusplus.com/reference/string/string/substr/
*/
#include <iostream>
#include <map>
#include <string>
#include <cassert>

using namespace std;

map<string, string> translator;

void store(string);
void unitTest();
void solve();

int main(int argc, char* argv[]){
    solve();
}

void solve(){
    string input;
    while(getline(cin, input) && input != ""){
        store(input);
    }
    while(getline(cin, input)){
        if(input == ""){
            break;
        }
        
        if(translator.find(input) != translator.end()){
            cout << translator[input] << endl;
        } else{
            cout << "eh\n";
        }
    }
}

void store(string input){
    string eng, trans;
    int spot = input.find(" ");
    eng = input.substr(0, spot);
    trans = input.substr(spot + 1); //spot + 1 so that space isnt included
    // store eng as a, trans as b in translator: {a, b}
    //cout << eng << " " << trans << endl; // testing purposes
    translator[trans] = eng;
    //translator.insert({eng, trans}); //<= Alternative

}