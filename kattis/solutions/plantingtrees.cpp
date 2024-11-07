#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int seeds, result=0;
    cin >> seeds;
    int days[seeds], min[seeds];
    for (int i = 0; i < seeds; i++) {
        cin >> days[i];
    }
    sort(days, seeds + days);
    for (int i = 0; i < seeds; i++) {
        min[i] = days[i] + seeds - i;
    }
    sort(min, seeds + min, greater<int>());
    cout << min[0] + 1 << endl;
    return 0;
}