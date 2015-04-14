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
	static string TryLogin(string name, string pass);
	static string CreateNewUser(string name, string pass);
	bool CheckConnection(); // temp storage?
	string Defend(int unit); // temp storage

private:
	bool ConfirmUser(string name, string pass);
	string Encrypt(string pass);



};

