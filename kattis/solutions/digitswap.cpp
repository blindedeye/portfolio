#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

int main(){
    string num;
    char a, b;
    cin >> num;
    const char* str = num.c_str();
    b = str[0];
    a= str[1];
    cout << a << b;
    
    return 0;
}