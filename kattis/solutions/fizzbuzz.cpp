#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

int game(int, int, int);

int main(int argc, char* argv[]) {
    int x, y, n;
    cin >> x >> y >> n;
    game(x, y, n);
    return 0;
  }

  int game(int x, int y, int n){
    for(int i = 1; i <= n; i++){
      if(i % x == 0 && i % y == 0){
        cout << "FizzBuzz" << endl;
      } else if(i % x == 0 && i % y != 0){
        cout << "Fizz" << endl;
      } else if(i % y == 0 && i % x != 0){
        cout << "Buzz" << endl;
      } else{
        cout << i << endl;
      }
    }
    return 0;
  }