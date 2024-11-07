/*
Falling Apart
Jake Peterson
1 November 2022
*/

#include <iostream>
#include <string>
#include <cassert>
#include <bits/stdc++.h>

using namespace std;

void unitTest();
void readData(unsigned int *, size_t);
void sort(unsigned int *, size_t);
int solve(unsigned int *, size_t);

int main(int argc, char* argv[]) {
  if (argc == 2 and string(argv[1]) == string("test")) {
    unitTest();
  }
  else {
    int s;
    cin >> s;
    unsigned int * pieces = new unsigned int [s];
    readData(pieces, s);
    sort(pieces, s);
    solve(pieces, s);
    return 0;
  }
}

void readData(unsigned int * pieces, size_t arr_len) {
  for(int i=0; i<arr_len; i++) {
    cin >> pieces[i];
  }
}

int solve(unsigned int * pieces, size_t arr_len) {
    int a = 0, b = 0;
    for (int x = 0; x < arr_len; x++){
        if ((x & 1) == 0){
            a += pieces[x];
          } else{
            b += pieces[x];
          }
        }
    cout << a << ' ' << b;
    return a;
}

void sort(unsigned int * pieces, size_t arr_len)
{
    int i, j, temp;
    bool sorted = false;
    for (i = 0; i < arr_len; i++) {
        sorted = true;
        for (j = 0; j < arr_len-i-1; j++) {
            if (pieces[j] < pieces[j+1]) {
        swap(pieces[j], pieces[j+1]);
                sorted = true;
            }
        }
        if (!sorted) break;
    }
}

void unitTest() {
    unsigned int * test = new unsigned int[4];
    test[0] = 4;
    test[1] = 3;
    test[2] = 2;
    test[3] = 1;
    assert(solve(test, 4) == 6);

    test[0] = 4;
    test[1] = 2;
    test[2] = 2;
    test[3] = 1;
    assert(solve(test, 4) == 6);

    test[0] = 1;
    test[1] = 1;
    test[2] = 1;
    test[3] = 1;
    assert(solve(test, 4) == 2);

    test[0] = 3;
    test[1] = 3;
    test[2] = 2;
    test[3] = 1;
    assert(solve(test, 4) == 5);

    cerr << "All test cases passed!";
}