#include <iostream>
#include <string>

using namespace std;

void solve();
string answer(const string &line);

int main(int argc, char* argv[]) {
    solve();
}

string answer(const string &line){
  int lineLength = line.length();
  string compact(1, line[0]);
  for(int i = 1; i < lineLength; i++){
    if(line[i] != line[i-1]){
      compact += line[i];
    }
  }
  return compact;
}

void solve(){
  string line;
  getline(cin, line);
  cout << answer(line) << endl;
}