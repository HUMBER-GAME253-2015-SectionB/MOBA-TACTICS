#pragma once
#include <iostream>
#include <fstream>
#include <string>
/*
//James Finnie
Last Updated 04/07
*/
using namespace std;

class Login
{
public:
	Login();
	~Login();
	string TryLogin(int id, string name, string pass);
	string CreateNewUser(string name, string pass);
	bool CheckConnection(); // temp storage?

private:
	bool ConfirmUser(string name, string pass);
	string Encrypt(string pass);

	

};

