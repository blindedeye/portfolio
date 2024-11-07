/*
Kattis - What does the fox say?
Vector Lab
Updated By: Jake Peterson
CSCI 111
Date: 4 November 2022
Read and solve the Kattis problem: https://open.kattis.com/problems/whatdoesthefoxsay
Algorithm Steps:
    1. For each test case do the following:
    i. Read all the recorded sounds into a vector
    ii. Read individual animal sound until 'What does the fox say?' line
      a) Erase all the matching animal sounds from the recorded sounds vector
    iv. Print the sounds that's left in the recorded sounds vector
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


void solve();
void splitString(vector<string> &, string);
void eraseAnimalSound(vector<string> &, string);
string foxSays(vector<string> &);
void test_eraseAnimalSound();
void test_splitString();
void test_foxSays();
void unit_test();

int main(int argc, char* argv[]) {
  if (argc == 2 and string(argv[1]) == string("test")) {
    unit_test(); // FIXME - FIXED
  }
  else
    solve();
  return 0;
}

void solve() {
  size_t T;
  cin >> T >> ws;

  while(T--) {
    cerr << "T = " << T << endl;
    vector<string> recordings;
    string sounds, animal_sound;
    getline(cin, sounds);
    cerr << sounds << endl;
    splitString(recordings, sounds);


    while (true) {
      getline(cin, animal_sound);
      if (animal_sound == "what does the fox say?") break;
      istringstream iss(animal_sound);
      string animal, goes, sound;
      iss >> animal >> goes >> sound;
      eraseAnimalSound(recordings, sound);
    }
      cout << foxSays(recordings) << endl; // FIXME2: FIXED
  }
}

string foxSays(vector<string> &recordings) {
  ostringstream oss;
  bool first = true;
  for(int i=0; i<recordings.size(); i++) {
    if (first) {
      oss << recordings[i];
      first = false;
    }
    else
      oss << " " << recordings[i];
  }
  return oss.str();
}

void splitString(vector<string> &words, string text) {
    string word;
    stringstream ss(text);
    while (ss >> word) {
        words.push_back(word);
    }
}

void eraseAnimalSound(vector<string> &recordings, string sound) {
  // FIXME3 - FIXED
  for (vector<string>::iterator it = recordings.begin(); it != recordings.end();){
    if (*it == sound)
        it = recordings.erase(it);
    else
        it++;
}
}

void test_splitString() {
  vector<string> answer;
  splitString(answer, "word");
  vector<string> expected = {"word"};
  assert(answer == expected);

  answer.clear();
  splitString(answer, "two word");
  vector<string> expected1 = {"two", "word"};
  assert(answer == expected1);
  // FIXME4 - FIXED
  answer.clear();
  splitString(answer, "three word");
  vector<string> expected2 = {"three", "word"};
  assert(answer == expected2);

  answer.clear();
  splitString(answer, "jake too");
  vector<string> expected3 = {"jake", "too"};
  assert(answer == expected3);


  cerr << "splitString(): All test cases passed!)\n";
}

void test_eraseAnimalSound() {
  vector<string> recordings = {"bo", "boo", "meow", "bo", "ba", "wooon", "bo"};
  eraseAnimalSound(recordings, "bo");
  vector<string> expected = {"boo", "meow", "ba", "wooon"};
  assert(recordings == expected);
  // FIXME6: FIXED
  recordings.clear();
  recordings = {"too", "poo", "coo", "tow", "wow", "poo", "poo"};
  eraseAnimalSound(recordings, "poo");
  vector<string> expected1 = {"too", "coo", "tow", "wow"};

  recordings.clear();
  recordings = {"he", "boo", "he", "bo", "he", "he", "he"};
  eraseAnimalSound(recordings, "he");
  vector<string> expected2 = {"boo", "bo"};
  cerr << "eraseAnimalSound(): All test cases passed!" << endl;
}

void test_foxSays() {
  vector<string> recordings = {"bo", "boo", "meow", "bo", "ba", "wooon", "bo"};
  eraseAnimalSound(recordings, "bo");
  string ans = foxSays(recordings);
  cerr << "ans = " << ans << endl;
  assert(ans == "boo meow ba wooon");
  // FIXME5: fixed
  recordings.clear();
  recordings = {"too", "poo", "coo", "tow", "wow", "poo", "poo"};
  eraseAnimalSound(recordings, "poo");
  ans = foxSays(recordings);
  cerr << "ans = " << ans << endl;
  assert(ans == "too coo tow wow");

  recordings.clear();
  recordings = {"he", "boo", "he", "bo", "he", "he", "he"};
  eraseAnimalSound(recordings, "he");
  ans = foxSays(recordings);
  cerr << "ans = " << ans << endl;
  assert(ans == "boo bo");
  cerr << "foxSays(): All test cases passed!" << endl;
}

void unit_test() {
  test_splitString();
  test_eraseAnimalSound();
  test_foxSays();
  cerr << "All unit tests passed!" << endl;
}