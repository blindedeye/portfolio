#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int findMinimumScientists(int, int);

int main(){

  int articles, impact;
  cin >> articles >> impact;
  printf("%d", findMinimumScientists(articles, impact));

  return 0;
}

int findMinimumScientists(int articles, int impact){
  int result = articles * (impact - 1) + 1;
  return result;
}