/*
Calorie Tracker Program
With 5 user capable system
Designed and Implemented by: Jake Peterson
Final Project for CS2 -> Castleton
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include "userCheck.h"
#include "home.h"
#include "utility.h"
#include <dirent.h>

using namespace std;

void selectUserPrompt(){

}

void listUsers() {
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir ("./Users/"))!=NULL) {
        while ((ent = readdir (dir)) != NULL) {
            string filename(ent->d_name);
            if (filename.substr(filename.find_last_of(".") + 1) == "txt") {
                string username = filename.substr(0, filename.find_last_of("."));
                cout << "- " << username << endl;
            }
        }
        closedir (dir);
    } else {
        perror ("");
    }
}

void readUsers(Users all, string selUser) {
    string userPath = "./Users/";
    ifstream ufile(userPath + selUser + ".txt");
    float goalCals, weight;
    map<Day, CaloryItems> dayData;
    if (ufile.good()) {
        ufile >> goalCals;
        ufile >> weight;
        string line;
        while (getline(ufile, line)) {
            int day;
            istringstream iss(line);
            string name;
            int calories;
            if(!(iss >> day)){ continue; }
            bool hasItems=false;
            while (iss >> name >> calories) {
                // Add the food item and its calories to the current day
                dayData[day].addItem(CalItem(calories, name));
                hasItems=true;
            }
            if(!hasItems){ dayData[day]=CaloryItems(); }
        }
        all.createUser(User(selUser, goalCals, weight, dayData));
    }
    clearScreen();
    User selectedUser = all.pickUser(all, selUser);
    int day;
    day = selectDay(selectedUser);
    home(selectedUser, day);
}


int main(){
    Users all;
    string selUser;
    clearScreen();

    cout << "Please Select a user (to make a new user enter desired name):" << endl;
    listUsers(); // Listing Users from .txt in folderpath
    cout << "Enter an Option >> ";
    cin >> selUser;
    readUsers(all,selUser);
    // if you want to go back a day call prev day function
    // if you want to go forward a day call next day function
    // if you want to add calories/food*/
    return 0;
}