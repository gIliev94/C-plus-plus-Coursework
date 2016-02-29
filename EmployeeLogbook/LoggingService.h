#pragma once
#include <fstream>

#include "Employee.h"

using namespace std;


class LoggingService
{
public:
	static void openLog();
	static void closeLog();
	static bool isLogOpened();
	static void logEmployees(vector<Employee> employees);
	static void logNewEmployeeSalaries(vector<Employee> employees);
private:
	LoggingService();
	~LoggingService();
	static void updateSalaryStatistics();
	static ifstream salaryStatisticsIn;
	static ofstream salaryStatisticsOut;
	static ofstream employeeLogBook;
};