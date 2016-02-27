#include <iomanip>
#include <algorithm>
#include <string>

#include "LoggingService.h"
#include "ConfigurationConstants.h"

using namespace std;


ifstream LoggingService::salaryStatisticsIn;
ofstream LoggingService::salaryStatisticsOut;
ofstream LoggingService::employeeLogBook;

void LoggingService::logEmployees(vector<Employee>& employees)
{
	for each (Employee employee in employees)
	{
		employeeLogBook << "Employee full name: " << employee.fullName.content << endl;
		employeeLogBook << "Employee personal id number: " << employee.id << endl;
		employeeLogBook << "Employee salary: $" << setprecision(2) << fixed << employee.salary << endl;
		employeeLogBook << "--------------------------------------------------------" << endl;
	}
}

void LoggingService::logNewEmployeeSalaries(vector<Employee>& employees)
{
	salaryStatisticsOut.open("../employeeSalariesMap.txt", fstream::app);

	for each (Employee employee in employees)
	{
		salaryStatisticsOut << employee.id << ConfigurationConstants::COLON << employee.salary << endl;
	}

	salaryStatisticsOut.close();

	updateSalaryStatistics();
}

void LoggingService::updateSalaryStatistics()
{
	vector<double> salaries;
	double newSalary = 0.0;

	string newSalaryEntry = ConfigurationConstants::EMPTY_STRING;

	salaryStatisticsIn.open("../employeeSalariesMap.txt", ifstream::in|ifstream::out);

	while (getline(salaryStatisticsIn, newSalaryEntry))
	{
		size_t pos = newSalaryEntry.find(ConfigurationConstants::COLON);
		newSalary = atof(newSalaryEntry.substr(pos + 1).c_str());
		salaries.push_back(newSalary);
	}

	salaryStatisticsIn.close();

	sort(salaries.rbegin(), salaries.rend());

	salaryStatisticsOut.open("../employeeTopSalariesChart.txt", fstream::out);

	int position = 1;
	for each (double salary in salaries)
	{
		if (position > 10)
		{
			break;
		}

		salaryStatisticsOut << position << ConfigurationConstants::PERIOD << setprecision(2) << fixed << "$" << salary << endl;
		position++;
	}

	salaryStatisticsOut.close();
}

void LoggingService::openLog()
{
	employeeLogBook.open("../employeeLogBook.txt", fstream::app);
}

void LoggingService::closeLog()
{
	employeeLogBook.close();
}

bool LoggingService::isLogOpened()
{
	if (!employeeLogBook.is_open())
	{
		cout << "No logbook available!" << endl << endl;
		return false;
	}
	else 
	{
		cout << "Successfully opened employee logbook!" << endl;
	}

	return true;
}

LoggingService::LoggingService()
{
}

LoggingService::~LoggingService()
{
}