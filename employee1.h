#ifndef EMPLOYEE1_H
#define EMPLOYEE1_H
#include "date1.h"
#include <string>
using namespace std;
class Employee{
    public: 
        Employee(const string, const string, const Date &, const Date & );
	void print () const;
	~Employee();
    private:
	string firstName;
	string lastName;
	const Date birthDate;
	const Date hireDate;
};
#endif
