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

void Login::TryLogin()
{
	cout << "Enter user name:" << endl;
	cin >> userName;

	//hide keys?
	cout << "Enter password:" << endl;
	cin >> password;

	if (ConfirmUser(userName, password))
	{
		//pass off to lobby
		cout << "It worked!";
	}
	else
	{
		cout << "nope, try again";
		//try again
		TryLogin();
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

void Login::CreateNewUser()
{
	string newName;
	string newPass;
	string passConfirm;
	bool done = false;

	while (!done)
	{
		cout << "Choose a user name:" << endl;
		cin >> newName;

		//hide these?
		cout << "Enter a password:" << endl;
		cin >> newPass;

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
			
			done = true;
		}
		else
		{
			cout << "Passwords don't match!";
		}
	}
	Login();
}

void Login::Clear()
{
	userName = "";
	password = "";
}