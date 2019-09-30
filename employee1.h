#ifndef EMPLOYEE1_H
#define EMPLOYEE1_H
#include "date1.h"
#include <string>
class Employee{
    public: 
        Employee(const char *, const char *, const Date &, const Date & );
	void print () const;
	~Employee();
    private:
	string firstName[25];
	string lastName[25];
	const Date birthDate;
	const Date hireDate;
};
#endif
