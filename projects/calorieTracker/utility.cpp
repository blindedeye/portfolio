#include <iostream>

using namespace std;

void clearScreen(){
    #ifdef _WIN32
        system("clS");
    #else
        system("clear");
    #endif
}