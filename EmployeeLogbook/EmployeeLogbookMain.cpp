#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <limits>

#include "Employee.h" 
#include "EnhancedString.h"
#include "LoggingService.h"
#include "ConfigurationConstants.h"

using namespace std;


EnhancedString getNameFromInput();
EnhancedString getNameFromInput(char space);
void setupEmployee(Employee* employee, EnhancedString wrapper, unsigned long long pid, double stateSalary);
void printRecords(vector<Employee> employees);
bool saveEmployeeRecord(Employee employeeRecord, vector<Employee>* records);
bool hasValidContent(EnhancedString wrapper);
bool isExitSelected();
double roundUpSalary(double stateSalary);

int main() 
{
	cout << "Welcome to the employee logging system! Attempting to open log book..." << endl;
	LoggingService::openLog();

	if (!LoggingService::isLogOpened()) 
	{
		cout << "Exitting now..." << endl;
		return 0;
	}
	cout << "Employee logging process started..." << endl << endl;

	vector<Employee> employeeRecords;
	unsigned long long id = 0;
	double salary = 0.0;

	bool shouldExit = false;
	do 
	{
		cout << "Enter first name for record[" << employeeRecords.size()+1 << "]: ";
		EnhancedString firstNameWrapper = getNameFromInput();

		cout << "Enter middle name for record[" << employeeRecords.size() + 1 << "]: ";
		EnhancedString middleNameWrapper = getNameFromInput(ConfigurationConstants::SPACE);

		cout << "Enter last name for record[" << employeeRecords.size() + 1 << "]: ";
		EnhancedString lastNameWrapper = getNameFromInput(ConfigurationConstants::SPACE);
		
		cout << "Enter id number: ";
		cin >> id;

		cout << "Enter salary: ";
		cin >> salary;

		EnhancedString fullNameWrapper = firstNameWrapper + middleNameWrapper + lastNameWrapper;

		Employee employee;
		setupEmployee(&employee,fullNameWrapper,id,salary);

		if (!saveEmployeeRecord(employee, &employeeRecords)) 
		{
			continue;
		}

		shouldExit = isExitSelected();
		cout << endl;
	} while (!shouldExit);

	cout << endl << "Logging records..." << endl;
	LoggingService::logEmployees(employeeRecords);
	cout << "Logged [" << employeeRecords.size() << "] new records!" << endl;

	cout << endl << "( UNSORTED ) Records["<< employeeRecords.size() <<"] :" <<endl;
	printRecords(employeeRecords);

	cout << endl << "Sorting records... " << endl;
	Employee::sortBySalaryDesc(&employeeRecords);

	cout << endl << "( SORTED by salary DESCENDING ) Records[" << employeeRecords.size() << "] :" << endl;
	printRecords(employeeRecords);
	
	cout << endl << "Logging and updating statistical data..." << endl;
	LoggingService::logNewEmployeeSalaries(employeeRecords);
	cout << "Logging/Updating statistics finished. Top salaries chart is now up to date!" << endl;

	LoggingService::closeLog();
	cout << "Exitting now..." << endl;

	system("pause");
	return 0;
}

void printRecords(vector<Employee> employees) 
{
	if (employees.size() == 0)
	{
		cout << "No employees to show!" << endl;
		return;
	}

	for each (Employee employee in employees)
	{
		cout << "Employee full name: " << employee.fullName.content << endl;
		cout << "Employee personal id number: " << employee.id << endl;
		cout << "Employee salary: " << employee.salary << endl;
	}
}

double roundUpSalary(double stateSalary)
{
	return floor(stateSalary * 100 + 0.5) / 100;
}

bool isExitSelected()
{
	char exitChoice = 0;

	do {
		cout << endl << "Stop logging now? (Y|N):";
		cin >> exitChoice;

		exitChoice = tolower(exitChoice);

		if (exitChoice == ConfigurationConstants::YES)
		{
			return true;
		}
		else if (exitChoice == ConfigurationConstants::NO)
		{
			break;
		}
		else {
			cout << "Invalid exit choice... Try again!" << endl;
		}
	} while (true);

	return false;
}

EnhancedString getNameFromInput()
{
	string name = ConfigurationConstants::EMPTY_STRING;

	cin >> ws;
	std::getline(cin >> ws, name);
	
	return EnhancedString(name, name.length());
}

EnhancedString getNameFromInput(char prefix)
{
	string name = ConfigurationConstants::EMPTY_STRING;
	
	cin >> ws;
	std::getline(cin, name);

	return EnhancedString(prefix + name, name.length()+1);
}

bool hasValidContent(EnhancedString wrapper) 
{
	if (wrapper.content == ConfigurationConstants::EMPTY_STRING)
	{
		cout << endl << "Name missing, record won`t be saved! Resetting input... " << endl << endl;
		return false;
	}

	return true;
}

void setupEmployee(Employee* employee, EnhancedString nameWrapper, unsigned long long pid, double stateSalary)
{
	if (employee == nullptr)
	{
		return;
	}

	employee->fullName = nameWrapper;
	employee->id = pid;
	employee->salary = roundUpSalary(stateSalary);
}

bool saveEmployeeRecord(Employee employeeRecord, vector<Employee>* records)
{
	if (records == nullptr || !hasValidContent(employeeRecord.fullName))
	{
		return false;
	}

	if (Employee::hasValidId(employeeRecord) && Employee::hasValidFullName(employeeRecord))
	{
		records->push_back(employeeRecord);
	}
	else
	{
		cout << "ID/name value/s is/are breaking rule/s for length/legal characters, record won`t be saved! Resetting input... " << endl << endl;
		return false;
	}

	return true;
}