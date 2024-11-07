#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    string words[n];
    for(int i=0; i < n; i++){
        cin >> words[i];
    }

    for(int f = 0; f < n; f++){
        if(f % 2 == 0){
            cout << words[f] << endl;
        }
    }
    return 0;
}