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
	
private:
	void TryLogin();
	bool ConfirmUser(std::string name, std::string pass);
	void CreateNewUser();
	void Clear();

	string userName;
	string password;
	

};

