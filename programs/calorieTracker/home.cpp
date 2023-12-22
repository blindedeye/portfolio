#include <iostream>
#include <iomanip>
#include <string>
#include "userCheck.h"
#include "utility.h"

using namespace std;

void home(User&,int);

int selectDay(User selectedUser){
    int inDay;
    cout << setfill('*') << setw(50) << "\n\n" << 
    selectedUser.getFirst() << 
    ", which day would you like to track?\n" << 
    "Past 7 days:\n"; 
    selectedUser.printDays(); 
    cout << setfill('*') << setw(50) << "\n\n";
    do{
        cout << "Enter an Option >> ";
        cin >> inDay;
    } while(!selectedUser.isDay(inDay));
    clearScreen();
    return inDay;
}

void addCalsPage(User& user, int day){
    string itemName;
    int calories;
    clearScreen();
    cout << setfill('*') << setw(50) << "\n\n" << 
    "Calorie Tracker - Add Calories" << "\n" <<
    "   Hello, " << user.getFirst() << "!\n\n" <<
    "What item are you adding?\n\n" <<
    setfill('*') << setw(50) << "\n\n" <<
    "Enter an Option >> ";
    cin >> itemName;
    clearScreen();
    cout << setfill('*') << setw(50) << "\n\n" << 
    "Calorie Tracker - Add Calories" << "\n" <<
    "   Hello, " << user.getFirst() << "!\n\n" <<
    "Great! How many calories of " << itemName << " did you consume?\n\n" <<
    setfill('*') << setw(50) << "\n\n" <<
    "Enter an Option >> ";
    cin >> calories;
    clearScreen();
    cout << setfill('*') << setw(50) << "\n\n" << 
    "Calorie Tracker - Add Calories" << "\n" <<
    "\n\nSuccessfully Added!\n\n" <<
    setfill('*') << setw(50) << "\n\n" <<
    "Press Enter to continue >> ";
    cin.ignore(100, '\n');
    cin.get();

    user.getDayData(day)->addItem(CalItem(calories, itemName));
    

    clearScreen();
    home(user,day);
}

void removeCalsPage(User& user, int day){
    string itemName;
    clearScreen();
    cout << setfill('*') << setw(50) << "\n\n" << 
    "Calorie Tracker - Remove Calories" << "\n" <<
    "   Hello, " << user.getFirst() << "!\n\n" <<
    "What item would you like to remove?\n\n" <<
    setfill('*') << setw(50) << "\n\n" <<
    "Enter an Option >> ";
    cin >> itemName;
    clearScreen();
    if(user.getDayData(day)->removeItem(itemName)){
        cout << setfill('*') << setw(50) << "\n\n" << 
        "Calorie Tracker - Remove Calories" << "\n" <<
        "\n\nSuccessfully Removed!\n\n" <<
        setfill('*') << setw(50) << "\n\n" <<
        "Press Enter to continue >> ";
        cin.ignore(100, '\n');
        cin.get();
    }else{
        cout << setfill('*') << setw(50) << "\n\n" << 
        "Calorie Tracker - Remove Calories" << "\n" <<
        "\n\nItem not found\n\n" <<
        setfill('*') << setw(50) << "\n\n" <<
        "Press Enter to continue >> ";
        cin.ignore(100, '\n');
        cin.get();
    }

    clearScreen();
    home(user,day);
}


void listCalsPage(int day,User& user){
    clearScreen();
    cout << setfill('*') << setw(50) << "\n\n" << 
    "Calorie Tracker - Items List" << "\n\n";
    user.getDayData(day)->listItems(user);
    cout << "\n" << setfill('*') << setw(50) << "\n\n" <<
    "Press Enter to continue >> ";
    cin.ignore(100, '\n');
    cin.get();
    clearScreen();
    home(user,day);
}

void saveAndQuit(User& user){
    user.saveUser(user);
    cout << "Successfully Saved!\nPress enter to exit >> ";
    cin.ignore(100, '\n');
    cin.get();
    exit(0);
}


void option(int pick,User user,int day){
    switch(pick){
        case 1:
            addCalsPage(user,day);
            break;
        case 2:
            removeCalsPage(user,day);
            break;
        case 3:
            listCalsPage(day,user);
            break;
        case 4:
            saveAndQuit(user);
            break;
        default:
            cout << "Please enter a number between 1-4 >> ";
            cin >> pick;
            option(pick,user,day);
            break;
    }
}

void home(User& selUser, int day){
    int pick;
    cout << setfill('*') << setw(50) << "\n\n" << 
    "Calorie Tracker - Day " << day << "\n" <<
    "   Hello, " << selUser.getFirst() << "!\n\n" <<
    "1. Add Item\n" <<
    "2. Remove Item\n" <<
    "3. List All Items\n" <<
    "4. Save and Quit\n\n" <<
    setfill('*') << setw(50) << "\n\n" <<
    "Enter an Option >> ";
    cin >> pick;
    option(pick, selUser, day);
}

