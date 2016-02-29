#pragma once
#include <vector>
#include <iostream>

#include "EnhancedString.h"

using namespace std;


class Employee
{
public:
	Employee();
	~Employee();
	static void sortBySalaryDesc(vector<Employee> *employees);
	static bool hasValidId(Employee employee);
	static bool hasValidFullName(Employee employee);
	bool operator>(Employee anotherEmployee);
	EnhancedString fullName;
	unsigned long long id;
	double salary;
};