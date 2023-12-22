#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include "userCheck.h"
#include "utility.h"
#include "home.h"

using namespace std;

User::User(string _first, float _calories, float _weight, map<Day, CaloryItems> _dayData){
    first = _first;
    calories = _calories;
    weight = _weight;
    dayData = _dayData;
}
bool User::isNamed(string other){ return first == other; }
string User::getFirst(){ return first; }
bool User::isDay(int in){
    for (const auto& day : dayData) {
        if(day.first.getDayNum()==in){
            return true;
        }
    }
    return false;
}
void User::printDays(){
    if (dayData.empty()) {
        cout << "No days available." << endl;
        return;
    }
    for (const auto& day : dayData) {
        cout << "- Day " << day.first.getDayNum() << endl;
    }
}
CaloryItems* User::getDayData(int day){
    auto it=dayData.find(day);
    if (it==dayData.end())
        return nullptr;
    else
        return &(it->second);
}
void User::saveUser(User user){
    ofstream file("./Users/"+user.getFirst()+".txt");
    if (file.is_open()) {
        file << calories << endl;
        file << weight << endl;
        for (const auto& day : user.dayData) {
            file << day.first.getDayNum() << " ";
            for (const auto& item : day.second.getItems()) {
                file << item.getName() << " " << item.getCals() << " ";
            }
            file << endl;
        }
        // 1 Burger 900 Sandwich 500 Sucker 300
        // 2 Candy 100
        file.close();
    }
}

void Users::createUser(User c){
    users[num] = c;
}

User Users::pickUser(Users all, string name){
    char yn;
    float calories, weight;
    for(User& u : all.users){
        if(u.isNamed(name)){
            return u;
        }
    }
    cout << "It appears that " << name << " is not a user!" << endl 
         << "Would you like to make it one? (y/n): ";
    cin >> yn;
    if(yn == 'Y' || yn == 'y'){
        
            clearScreen();
            cout << "How many calories are you trying to eat daily? >> ";
            cin >> calories;
            cout << "How much do you weigh? >> ";
            cin >> weight;
            clearScreen();
            map<Day, CaloryItems> dayData;
            dayData[Day(1, vector<CaloryItems>())] = CaloryItems(); // Add default day 1
            all.createUser(User(name, calories, weight, dayData));
            ofstream fuser("./Users/"+name+".txt");
            fuser << calories << endl;
            fuser << weight << endl;
            fuser << "1" << endl; // Write default day 1
            fuser.close();
            return all.users[num];
        
    } 
    return User(); // basically if all fails, then return a NULL constructed User
}

void Users::listAll() {
    cout << "Users:" << endl;
        for (int i=0;i<num;i++) {
            cout << "- " << users[i].getFirst() << endl;
    }
}

Day::Day(int _dayNum,vector<CaloryItems> _items){
    dayNum=_dayNum;
    items=_items;
}
bool Day::isDay(int day){ return day==dayNum; }
void Day::printDay(){ cout << "- Day " << dayNum << endl; }
int Day::getDayNum()const{ return dayNum; }




CalItem::CalItem(int _calories,string _itemName){
    calories=_calories;
    itemName=_itemName;
}
void CalItem::printCals()const{ cout << calories; }
void CalItem::printName()const{ cout << itemName; }
string CalItem::getName()const{ return itemName; }
int CalItem::getCals()const{ return calories; }

CaloryItems::CaloryItems(vector<CalItem> _items){ items=items; }
vector<CalItem> CaloryItems::getItems() const { return items; }
void CaloryItems::addItem(CalItem item){ items.push_back(item); }
void CaloryItems::listItems(User u){
    if (items.empty()) {
        cout << "No items yet" << endl;
        return;
    }
    for (const auto& item : items) {
        cout << " - ";
        item.printName();
        cout << ": ";
        item.printCals();
        cout << " calories" << endl;
    }
}
bool CaloryItems::removeItem(string itemName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getName() == itemName) {
                items.erase(it);
                return true;
            }
        }
        return false;
    }


bool operator<(const Day& lhs, const Day& rhs){ return lhs.dayNum < rhs.dayNum; }

