#pragma once
#include <iostream>
#include <fstream>
#include <string>
/*
//James Finnie
Last Updated 03/11
*/
using namespace std;

class Login
{
public:
	Login();
	~Login();
	
	static string TryLogin(string, string);
	bool ConfirmUser(std::string name, std::string pass);
	static string CreateNewUser(string, string);
	void Clear();

private:
	string userName;
	string password;
	

};

