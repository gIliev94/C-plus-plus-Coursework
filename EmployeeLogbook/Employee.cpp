#include "Employee.h"
#include "ConfigurationConstants.h"


Employee::Employee()
{
	id = 0;
	double salary = 0.0;
}

Employee::~Employee()
{
}

bool Employee::operator>(Employee& anotherEmployee)
{
	if ((&anotherEmployee) == NULL)
	{
		return false;
	}

	if (anotherEmployee.salary > this->salary) 
	{
		return true;
	}

	return false;
}

void Employee::sortBySalaryDesc(vector<Employee>* employees)
{
	if (employees == NULL) 
	{
		return;
	}

	Employee temp;

	for (unsigned int i = 0; i < (employees->size() - 1); i++)
	{
		for (unsigned int j = 0; j < (employees->size() - i - 1); j++)
		{
			if (employees->at(j) > employees->at(j + 1))
			{
				temp = employees->at(j);
				employees->at(j) = employees->at(j + 1);
				employees->at(j + 1) = temp;
			}
		}
	}

}

bool Employee::hasValidId(Employee employee)
{
	string personalId = to_string(employee.id);

	if (personalId.length() != ConfigurationConstants::ID_LENGTH) {
		cout << endl << "Invalid input: Perosnal ID must be EXACTLY ["<< ConfigurationConstants::ID_LENGTH <<"] digits long!" << endl;
		return false;
	}

	return true;
}

bool Employee::hasValidFullName(Employee employee)
{
	string stringContent = employee.fullName.content;

	for each (char c in stringContent)
	{
		if (!isalpha(c) && c != ConfigurationConstants::SPACE)
		{
			cout << endl << "Invalid input: Name should only contain letters!" << endl;
			return false;
		}
	}

	return true;
}