#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    string inString, key="simon says";
    cin >> n;
    cin.ignore();
    for(int i=0; i<n; i++) {
        string inString;
        getline(cin, inString);
        if(inString.rfind(key, 0) == 0) {
            inString.erase(0, 11);
            cout << inString << endl;
        }
        else
            cout << endl;
    }
}