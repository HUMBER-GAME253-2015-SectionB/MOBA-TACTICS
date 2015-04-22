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
	static string TryLogin(int id, string name, string pass);
	static string CreateNewUser(string name, string pass);
	bool CheckConnection(); // temp storage?

private:
	static bool ConfirmUser(string name, string pass);
	static string Encrypt(string pass);
};

