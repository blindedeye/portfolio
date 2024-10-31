#pragma once
#include <string>

using namespace std;

int selectDay(User);
void home(User&, int);
void option(int, User, int);
void addCalsPage(User&, int);
void listCalsPage(int,User&);
void removeCalsPage(User&,int);
void saveAndQuit(User&);