#include <iostream>
#include "date1.h"
using namespace std;
Date::Date(int mn, int dy, int yr){
    if (mn > 0 && mn < 13) month=mn;
    else {
	month = 1;
	cout << "NO!" << endl;
    }
    year = yr;
    day = checkDay(dy);
    cout << "Costruttore ha fatto cose";
    print();
    cout << endl;
}
void Date::print() const {
    cout << month << "/" << day <<"/" << year;
}
Date::~Date(){
    cout << "DISTRUZIONE!";
    print();
    cout << endl;
}
int Date::checkDay(int tD) const {
    static const int daysPerMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (tD > 0 && tD <=daysPerMonth[month]) return tD;
    if (month == 2 && tD == 29 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0 ))) return
	tD;
    cout << "NOOOOOOOOOO" << endl;
    return 1;
}

