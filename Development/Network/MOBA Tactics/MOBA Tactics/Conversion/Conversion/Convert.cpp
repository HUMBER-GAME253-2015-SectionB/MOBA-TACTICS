#include "Convert.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

void IntegerToString(string input)
{
	string result;
	string String = static_cast<ostringstream*>(&(ostringstream() << input))->str();

	cout << "Int to String: " + String << endl;
}

void StringToInteger(string input)
{
	int result;

	if (!(istringstream(input) >> result)) result = 0;

	cout << "String to Int: " << result << endl;
}

void CharArrayToString(string input)
{
	istringstream is;
	char buf[100]; //size of data being sent over

	is.str(input);
	is.getline(buf, sizeof buf);

	cout << "Char Array to String: " << buf << endl;
}

void StringToCharArray(string input)
{
	char *ca = new char[input.size() + 1]; //ca = character array
	ca[input.size()] = 0;
	memcpy(ca, input.c_str(), input.size());

	cout << "String to Char Array: " << ca << endl;
}

int main()
{
	string input; //input is simply a test to insert data - replace it with actual data being sent between client and server

	cout << "Enter an integer and/or word" << endl; //filler to tell user to input data
	getline(cin, input);

	//functions
	IntegerToString(input);
	StringToInteger(input); 
	CharArrayToString(input);
	StringToCharArray(input);

	system("pause");
	//return 0;
}

Convert::Convert()
{
}


Convert::~Convert()
{
}
