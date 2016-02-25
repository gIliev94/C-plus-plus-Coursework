#include <iostream>
#include <string>

#include "EnhancedString.h"
#include "ConfigurationConstants.h"

using namespace std;


EnhancedString::EnhancedString()
{
	length = 0;
	content = ConfigurationConstants::EMPTY_STRING;
	beginningPointer = NULL;
}

EnhancedString::~EnhancedString()
{
	beginningPointer = NULL;
}

EnhancedString::EnhancedString(string stringContent, unsigned int stringLength)
{
	for each (char c in stringContent)
	{
		if (!isValidCharacter(c)) 
		{
			cout <<endl<< "Contains invalid character - one that is not a period, space or a letter!" << endl;
			return;
		}
	}

	length = stringLength;
	content = stringContent;
	beginningPointer = &stringContent[0];
}

EnhancedString EnhancedString::operator+(const EnhancedString anotherString)
{
	if ((&anotherString) == NULL)
	{
		return *this;
	}

	content += anotherString.content;
	length += anotherString.length;
	beginningPointer = &content[0];

	return *this;
}

EnhancedString EnhancedString::operator=(const EnhancedString anotherString)
{
	if ((&anotherString) == NULL)
	{
		return *this;
	}

	content = anotherString.content;
	length = anotherString.length;
	beginningPointer = anotherString.beginningPointer;

	return *this;
}

bool EnhancedString::isValidCharacter(char c)
{
	bool isPeriodOrSpace = (c == ConfigurationConstants::PERIOD || c == ConfigurationConstants::SPACE);

	if (!isPeriodOrSpace && !isalpha(c))
	{
		return false;
	}

	return true;
}