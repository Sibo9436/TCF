#include <iostream>
#include "employee1.h"
#include "date1.h"
#include <string>
Employee::Employee(const string first, const string last, const Date &dateofBirth, const Date
&dateofHire):birthDate(dateofBirth), hireDate(dateofHire){
    firstName = first;
    lastName = last;
    cout << "Schiavo: " << firstName << " " << lastName<< endl;
}
void Employee::print() const{
    cout << lastName << ", " << firstName << "\nHired: ";
    hireDate.print();
    cout << " Birth date: " ;
    birthDate.print();
    cout << endl;
}
Employee::~Employee(){
    cout << "Addio, schiavo numero 666, tutti questi momenti andranno perduti, come lacrime nella pioggia" << endl;
}

