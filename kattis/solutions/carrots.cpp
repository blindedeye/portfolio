#include <iostream>
#include <string>

using namespace std;

int main(){
    int n1, n2;
    cin >> n1 >> n2;
    string desc[n1];
    for(int i=0; i<n1; i++){
        cin >> desc[i];
    }
    cout << n2;
    return 0;
}