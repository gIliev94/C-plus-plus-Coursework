#pragma once
#include <string>

using namespace std;


class EnhancedString
{
public:
	EnhancedString();
	~EnhancedString();
	EnhancedString(string stringContent, unsigned int strLength);
	EnhancedString operator=(const EnhancedString anotherString);
	EnhancedString operator+(const EnhancedString anotherString);
	string content;
	char* beginningPointer;
	unsigned int length;
private:
	bool isValidCharacter(char c);
};