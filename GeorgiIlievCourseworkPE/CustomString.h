#ifndef CUSTOMSTRING_H
#define CUSTOMSTRING_H
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string>
using namespace std;

class CustomString
{
public:
	CustomString();
	CustomString(char *outerString, const unsigned int stringLen);
	~CustomString();
	CustomString operator+(const CustomString anotherString);
	CustomString operator=(const CustomString anotherString);
	char *startPointer;
	unsigned int stringLength;
private:
	bool checkValidSymbol(char testedChar);
};


inline CustomString::CustomString()
{
	stringLength = 0;
}

CustomString::CustomString(char *outerString, unsigned int stringLen)
{
	stringLength = stringLen;
	startPointer = outerString;

	// SYMBOL VALIDATION
	for (int i = 0;i < stringLength;i++) 
	{
		// still some problems with validation
		if (checkValidSymbol(outerString[i])==1) 
		{
			startPointer[i] = outerString[i];
		}
		else 
		{
			startPointer = nullptr;
			break;
		}
	}
}

CustomString::~CustomString()
{
}

inline bool CustomString::checkValidSymbol(char testedChar)
{
	bool isValidSymbol = 1;
	bool conditionSymbolCheck = (isalpha(testedChar) == 0 && (testedChar != 46 && testedChar != 32));

	if (conditionSymbolCheck) 
	{
		cout << "\nInvalid input: Contains something that isn`t a letter,dot or a whitespace!" << endl;
		isValidSymbol = 0;
	}

	return isValidSymbol;
}

inline CustomString CustomString::operator+(const CustomString anotherString)
{
	// Acts as a buffer ( requires initialization - kinda hardcoded in )
	char *result = new char[4096];
	result[0] = 0;

	// This actually adds up the char arrays of the names ( sloppy solution but eh )
	strcat_s(result,1024,startPointer);
	strcat_s(result, 1024, anotherString.startPointer);

	unsigned int resultLength = stringLength + anotherString.stringLength;

	CustomString *resName = new CustomString(result, resultLength);
	return *resName;
}

inline CustomString CustomString::operator=(const CustomString anotherString)
{
	char *resultPointer = new char[4096];
	resultPointer[0] = 0;

	resultPointer = anotherString.startPointer;
	unsigned int resultLength = anotherString.stringLength;

	CustomString *resObj = new CustomString(resultPointer, resultLength);
	return *resObj;
}
#endif 