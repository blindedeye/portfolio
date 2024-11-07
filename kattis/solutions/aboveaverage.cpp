#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    float sum=0, average, go=0, aboveAverage=0;
    int cases, studCases;
    cin >> cases;
    float averages[cases];
    for(int i=0; i<cases; i++){
        cin >> studCases;
        float tempGrades[studCases];
        for(int j=0;j<studCases;j++){
            cin >> tempGrades[j];
        }
        for(int l=0; l<studCases; l++){
            sum += tempGrades[l];
    }
        average = sum / studCases;
        for(int m=0; m<studCases; m++){
            if(tempGrades[m] > average){
                aboveAverage++;
            }
        }
        averages[i] = (aboveAverage / studCases) * 100;
        go++;
        aboveAverage=0;
        sum=0;
    }
    for(int i=0; i<cases; i++){
        cout << fixed << setprecision(3) << averages[i] << "%" << endl;
    }
    return 0;
}