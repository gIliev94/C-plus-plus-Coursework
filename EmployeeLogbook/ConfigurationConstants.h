#pragma once
#include <string>

using namespace std;


class ConfigurationConstants
{
public:
	static const string EMPTY_STRING;
	static const char COLON;
	static const char SPACE;
	static const char PERIOD;
	static const char YES;
	static const char NO;
	static const int ID_LENGTH;
private:
	ConfigurationConstants();
	~ConfigurationConstants();
};