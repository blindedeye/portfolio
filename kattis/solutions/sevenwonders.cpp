/*
Map Lab
Kattis - Seven Wonders
Updatd By: Jake Peterson
01 December 2022
Solution to Seven Wonders Problem: https://open.kattis.com/problems/sevenwonders
Algorithm steps:
1. Read cards into a string variable
2. use map<char, int> to keep track of count of each card played
  - update map: for each card, update its count
3. find regular points following the instruction
  - points = sum of (each card_count)^2
4. add bonus points if any
  - find # of sets of three cards and mulitiply it by 7
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <map>
#include <string>

using namespace std;

using pos_int = unsigned int;


void countCards(const string&, map<char, pos_int>&);
pos_int countPoints(const map<char, pos_int>&);
pos_int countBonus(const map<char, pos_int>&);
void testCountCards();
void testCountPoints();
void testCountBonus();
void solve();
void unittest();

int main(int argc, char* argv[]){
    if(argc == 2 and string(argv[1]) == "test")
        unittest();
    else
        solve();
}

void solve(){
    string cards;
    pos_int points = 0;
    map<char, pos_int> cardCount;
    // FIXME1 - FIXED
    // read played cards into cards variable
    cin >> cards;
    
    // FIXME2 - FIXED
    // count cards - call countCards function passing cards and cardCount
    countCards(cards, cardCount);
    
    // FIXME3 - FIXED
    // count points - call countPoints function and update points
    points = countPoints(cardCount);
    //cout << points << endl;
    
    // FIXME4 - FIXED
    // count bonus points - call countBonus function and update points

    points += countBonus(cardCount);

    cout << points << endl;
}

void countCards(const string& cards, map<char, pos_int>& cardCount){
    for(char card : cards){
        auto find = cardCount.find(card);
        if(find == cardCount.end()){
            cardCount[card] = 1;
        } else{
            cardCount[card] += 1; //FIXME5 -
        }
    }
}

pos_int countPoints(const map<char, pos_int>& cardCount){
    pos_int points=0;
    for(auto pair : cardCount){
        points += pair.second * pair.second; //FIXME6 - 
    }
    return points;
}

pos_int countBonus(const map<char, pos_int>& cardCount){
    pos_int bonus = 0;
    pos_int minCardCount = 999999;
    pos_int uniqueCardCount = cardCount.size();
    if(uniqueCardCount == 3){
        for(auto pair : cardCount){
            minCardCount = pair.second < minCardCount? pair.second : minCardCount;
        }
        bonus = minCardCount * 7;
    }
    return bonus;
}

void unittest(){
    //FIXME10 - FIXED
    testCountCards();
    testCountPoints();
    testCountBonus();
}

void testCountCards(){
    map<char, pos_int> cardCount;
    countCards("TTT", cardCount);
    assert(cardCount['T'] == 3);

    cardCount.clear();
    countCards("TCG", cardCount);
    assert(cardCount['T'] == 1);
    assert(cardCount['C'] == 1);
    assert(cardCount['G'] == 1);

    //FIXME7 - FIXED
    cardCount.clear();
    countCards("TCTGC", cardCount);
    assert(cardCount['T'] == 2);
    assert(cardCount['C'] == 2);
    assert(cardCount['G'] == 1);

    cardCount.clear();
    countCards("CC", cardCount);
    assert(cardCount['C'] == 2);

    cerr << "[CountCards]: All cases passed.\n";
}

void testCountPoints(){
    map<char, pos_int> cardCount;
    countCards("TTT", cardCount);
    assert(countPoints(cardCount) == 9);
    
    cardCount.clear();
    countCards("TCG", cardCount);
    assert(countPoints(cardCount) == 3);

    //FIXME8 - FIXED
    cardCount.clear();
    countCards("CCC", cardCount);
    assert(countPoints(cardCount) == 9);

    cardCount.clear();
    countCards("TTCCGG", cardCount);
    assert(countPoints(cardCount) == 26);

    cerr << "[CountPoints]: All casses passed.\n";
}

void testCountBonus(){
    map<char, pos_int> cardCount;
    countCards("TTT", cardCount);
    assert(countBonus(cardCount) == 0);

    cardCount.clear();
    countCards("TCG", cardCount);
    assert(countBonus(cardCount) == 7);

    cardCount.clear();
    countCards("TTTCCCGG", cardCount);
    assert(countBonus(cardCount) == 14);

    //FIXME9 - FIXED
}