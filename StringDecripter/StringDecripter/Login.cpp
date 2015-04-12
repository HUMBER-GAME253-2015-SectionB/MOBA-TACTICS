/*
//James Finnie
Last Updated 03/11
*/

#include "stdafx.h"
#include "Login.h"



fstream loginInfo;

Login::Login()
{
	char choice;

	cout << "[l]ogin or [r]egister" << endl;

	cin >> choice;

	if (choice == 'l' || choice == 'L')
	{
		TryLogin();
	}
	else if (choice == 'r' || choice == 'R')
	{
		CreateNewUser();
	}
	else
	{
		Login();
	}


}


Login::~Login()
{
}

string Login::TryLogin(string userName, string password)
{
	if (ConfirmUser(userName, password))
	{
		//Get user info from database
		//getInfo(userName);
		//pass off to lobby
		return "l/l/true/userinfo/";
	}
	else
	{
		return "l/l/false/";
	}
}

bool Login::ConfirmUser(std::string name, std::string pass)
{
	bool found = false;

	string test = name + " " + pass;
	string line;

	//open file for reading
	loginInfo.open("loginInfo.txt");

	//look for a line that matches username and password
	while (getline(loginInfo, line) && found == false)
	{
		//if found set found to true
		if (line.compare(test) == 0)
		{
			found = true;
		}
	}
	//if found set found to true

	//close file
	loginInfo.close();

	return found;
}

string Login::CreateNewUser(string newName, string newPass)
{
	string passConfirm;

	cout << "Confirm password:" << endl;
	cin >> passConfirm;

	//make sure passwords match
	if (newPass == passConfirm)
	{
		//open file for writing and append to end
		loginInfo.open("loginInfo.txt", ios::app);
		
		//this may enter info weirdly, keep an eye...
		loginInfo << newName << " " << newPass << endl;
		
		loginInfo.close();
			
		return "l/r/true/";
	}
	else
	{
		return "l/r/false/";
	}
}

void Login::Clear()
{
	userName = "";
	password = "";
}