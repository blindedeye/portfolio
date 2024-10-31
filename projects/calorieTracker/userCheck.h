#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
const int MAXUSERS = 5;

class CaloryItems;
class Day;

class User{
    protected:
    string first;
    float calories, weight;
    map<Day,CaloryItems> dayData;
    public: 
    User(string _first="", float _calories=0.0, float _weight=0.0, map<Day, CaloryItems> _dayData=map<Day, CaloryItems>());
    string getFirst();
    CaloryItems* getDayData(int);
    bool isNamed(string);
    bool isDay(int);
    void printDays();
    void saveUser(User);                                                                                                                 
};

class Users:public User{
    int num=0;
    User users[MAXUSERS];
    public:
    void createUser(User);
    User pickUser(Users, string);
    void listAll();
    //bool checkUser(string);
};

bool operator<(const Day& lhs, const Day& rhs);

class Day:public User{
    protected:
    int dayNum;
    vector<CaloryItems> items;
    public:
    Day(int _dayNum=0,vector<CaloryItems> _days=vector<CaloryItems>());
    void printDay();
    bool isDay(int);
    int getDayNum() const;
    friend bool operator<(const Day& lhs, const Day& rhs);
};



class CalItem:public Day{
    protected:
    int calories;
    string itemName;
    public:
    CalItem(int _calories=0, string _itemName="");
    void printCals() const;
    void printName() const;
    string getName() const;
    int getCals() const;
};



class CaloryItems:public CalItem{
    protected:
    vector<CalItem> items;
    public:
    CaloryItems(vector<CalItem> _items = vector<CalItem>());
    vector<CalItem> getItems() const;
    void addItem(CalItem);
    bool removeItem(string);
    void listItems(User);
};
