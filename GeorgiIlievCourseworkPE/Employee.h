#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include "CustomString.h"
using namespace std;

class Employee
{
public:
	Employee();
	~Employee();
	bool operator>(const Employee anotherEmployee);
	unsigned long long getPersonId();
	double Employee::getStateSalary();
	void setPersonId(unsigned long long pId);
	void Employee::setStateSalary(double stSalary);
	string Employee::getFullName();
	void Employee::setFullName(string fName);
private:
	bool checkValidPid();
	bool checkValidName();
	unsigned long long personId;
	double stateSalary;
	string fullName;
};

Employee::Employee() {
	fullName = " ";
	personId = 0;
	double stateSalary = 0;
}

Employee::~Employee() {
}

inline unsigned long long Employee:: getPersonId() {
	return personId;
}

inline void Employee::setPersonId(unsigned long long pId) {
	personId = pId;
	if (checkValidPid() == 0) 
	{
		personId = 0;
	}
}

inline double Employee::getStateSalary() {
	return stateSalary;
}

inline void Employee::setStateSalary(double stSalary) {
	stateSalary = stSalary;
}

inline string Employee::getFullName() {
	return fullName;
}

inline void Employee::setFullName(string fName) {
	fullName = fName;
	if (checkValidName() == 0)
	{
		fullName = "0";
	}
}

inline bool Employee::checkValidName() {
	for (int i = 0; i < fullName.length();i++) {
		if (isalpha(fullName[i] == 0))
		{
			cout << "\nInvalid input: Name should only contain letters! " << endl;
			return 0;
		}
	}
}

inline bool Employee::checkValidPid()
{
	std::string pId = std::to_string(personId);

	if (pId.size() < 10 || pId.length() > 10) {
		cout << "\nInvalid input: Perosnal ID must be EXACTLY 10 digits long! " << endl;
		return 0;
	}
	return 1;
}

inline bool Employee::operator>(Employee anotherEmployee)
{
	if (anotherEmployee.getStateSalary() > stateSalary) {
		return 1;
	}
	return 0;
}
#endif 