#include "stdafx.h"
#include "Employee.h"
#include "CustomString.h"
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

// METHOD DECLARES
bool checkFileOpened();
bool checkCountInput();
bool checkDataIntegrity(vector<Employee> employeeData);
bool checkName(CustomString *name);
bool checkLogSafety(Employee em);
double roundUpSalary(double stSalary);
vector<Employee> populateEmployees(vector<Employee> employees);
vector<Employee> sortBySalaryDesc(vector<Employee> unsortedEmployees);
void printEmployeesInfo(vector<Employee> listedEmployees);
void logEmployee(Employee emp);

// GLOBAL VARS
ofstream employeeLogBook;
int numberOfEmployees = 0;

int main()
{
    cout << "Welcome to the employee logging system! Attempting to open logbook...\n" << endl;
	employeeLogBook.open("../empLog.txt", fstream::app);

	// LOGBOOK exsists
	if (checkFileOpened() == 0) return 0;

	// INPUT COUNT
	cout << "Specify how many employees you`d like to log : ";
	cin >> numberOfEmployees;
	cin.ignore();

	cout << endl;
	// COUNT INPUT valid
	if (checkCountInput() == 0) return 0;
	
	vector<Employee> employeeRecords(numberOfEmployees);

	// POPULATE, setup
	employeeRecords = populateEmployees(employeeRecords);

	// BREAK here if errors occured
	if(checkDataIntegrity(employeeRecords) == 0) return 0;

	// BEFORE
	cout << "Your Employee log ( BEFORE sort ):" << endl;
	printEmployeesInfo(employeeRecords);

	// SORT by bubble algorithm
	employeeRecords = sortBySalaryDesc(employeeRecords);

	// AFTER
	cout << "Your Employee log ( AFTER sort by salary DESC ):" << endl;
	printEmployeesInfo(employeeRecords);

	// END, CLEANUP
	employeeLogBook.close();

	cout << endl << "Logging of employees finished !" << endl;
	system("pause");
	return 0;
}

vector<Employee> populateEmployees(vector<Employee> employees) 
{
    string fNameInput = "";
	string mNameInput = "";
	string lNameInput = "";
	CustomString *firstName = nullptr;
	CustomString *middleName = nullptr;
	CustomString *lastName = nullptr;
	char *firstNamePtr;
	char *middleNamePtr;
	char *lastNamePtr;
	unsigned long long personalId;
	double stateSalary;

	for (int i = 0;i < numberOfEmployees;i++) {
		// INPUTS

		cout << "Employee( "<<(i+1)<<" )"<<"\nEnter empployee`s first name: ";
		cin.clear();

		getline(cin, fNameInput);
		fNameInput += " ";

		firstNamePtr = &fNameInput[0];
		firstName = new CustomString(firstNamePtr, fNameInput.length());

		if (checkName(firstName) == 0) {
			i = i - 1;// Set the record back on the current index
			continue;
		}

		cout << "\nEnter empployee`s middle name: ";
		getline(cin, mNameInput);
		mNameInput += " ";

		middleNamePtr = &mNameInput[0];
		middleName = new CustomString(middleNamePtr, mNameInput.length());

		if (checkName(middleName) == 0) {
			i = i - 1; 
			continue;
		}

		cout << "\nEnter empployee`s last name: ";
		getline(cin, lNameInput);

		lastNamePtr = &lNameInput[0];
		lastName = new CustomString(lastNamePtr, lNameInput.length());

		if (checkName(lastName) == 0) {
			i = i - 1;
			continue;
		}
		
		// The  DEFACTO fullName
		CustomString fullNameObject = *firstName + *middleName + *lastName;
		string fullName = fullNameObject.startPointer;

		cout << "\nEnter empployee`s personal ID: ";
		cin >> personalId;

		cout << "\nEnter empployee`s state salary: ";
		cin >> stateSalary;

		// CREATIO/SETTINGS
		Employee employee;

		employee.setPersonId(personalId);
		employee.setStateSalary(roundUpSalary(stateSalary));
		employee.setFullName(fullName);

		// SHIELD LOG if needed
		if (checkLogSafety(employee) == 0) {
			i = i - 1;
			continue;
		}

		// ASSIGN
		employees[i] = employee;

		// LOG
		logEmployee(employee);

		cout << endl<<endl;
	}
	delete firstName;
	delete middleName;
	delete lastName;
	return employees;
}

vector<Employee> sortBySalaryDesc(vector<Employee> unsortedEmployees)
{
	Employee swap;

	for (int c = 0; c < (unsortedEmployees.size() - 1); c++)
	{
		for (int d = 0; d < unsortedEmployees.size() - c - 1; d++)
		{
			if (unsortedEmployees[d]>unsortedEmployees[d + 1])
			{
				swap = unsortedEmployees[d];
				unsortedEmployees[d] = unsortedEmployees[d + 1];
				unsortedEmployees[d + 1] = swap;
			}
		}
	}
	return unsortedEmployees;
}

void logEmployee(Employee emp)	
{
	employeeLogBook << "Employee full name: ";
	employeeLogBook << emp.getFullName()<<endl;
	employeeLogBook << "Employee PID: ";
	employeeLogBook << emp.getPersonId() << endl;
	employeeLogBook << "Employee Salary: $";
	employeeLogBook << setprecision(2) << fixed << emp.getStateSalary() << endl;
	employeeLogBook << "--------------------------------------------------------"<<endl;
}

void printEmployeesInfo(vector<Employee> listedEmployees)
{
	for (int i = 0; i < listedEmployees.size(); i++)
	{
		cout << "Employee full name: " << listedEmployees.at(i).getFullName() << endl;
		cout << "Employee PID: " << listedEmployees.at(i).getPersonId() << endl;
		cout << "Employee Salary: $" << setprecision(2) << fixed << listedEmployees.at(i).getStateSalary() << endl;
		cout << endl;
	}
}

double roundUpSalary(double stSalary) 
{
	return floor(stSalary * 100 + 0.5) / 100;
}

bool checkName(CustomString *name)
{
	if (name->startPointer == nullptr)
	{
		cout << "\nInput invalidated, record won`t be kept! Starting over... " << endl<<endl;
		return 0;
	}
	return 1;
}

bool checkLogSafety(Employee em)
{
	if (em.getPersonId() == 0)
	{
		cout << "\nInput invalidated, record won`t be kept! Starting over..." << endl<<endl;
		cin.ignore();
		return 0;
	}
	else if (em.getFullName() == "0")
	{
		cout << "\nInput invalidated, record won`t be kept! Starting over..." << endl<<endl;
		return 0;
	}
	return 1;
}


bool checkDataIntegrity(vector<Employee> employeeData)
{
	for (int i = 0;i < employeeData.size();i++)
	{
		if (employeeData[i].getFullName() == "0" || employeeData[i].getPersonId() == 0)
		{
			cout << endl;
			employeeLogBook.close();
			system("pause");
			return 0;
		}
	}
	return 1;
}

bool checkFileOpened() 
{
	if (!employeeLogBook.is_open())
	{
		cout << "No logbook available!" << endl<< endl;
		employeeLogBook.close();
		system("pause");
		return 0;
	}
	else cout << "Successfully opened employee logbook!" << endl <<endl;

	return 1;
}

bool checkCountInput()
{
	std::string str = std::to_string(numberOfEmployees);
	if (str == "0")
	{
		cout << "\nInvalid input for count of loggable employees! Exitting now..." << endl<< endl;
		employeeLogBook.close();
		system("pause");
		return 0;
	}
	return 1;
}