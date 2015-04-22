/*
//James Finnie
Last Updated 04/07
*/
#pragma once
#include "stdafx.h"
#include "Login.h"
#include "Team.h"
#include "Players.h"

fstream loginInfo;

Login::Login()
{
}


Login::~Login()
{
}

string Login::TryLogin(int id, string name, string pass)
{
	if (ConfirmUser(name, pass))
	{
		//everything checks out!
		
		//register username for future use
		Player newPlayer = Players::FindPlayerByID(id);
		newPlayer.userName = name;

		//confirm and send teams from DB (why is this combined?)
		//oh well...

		//populates users stored teams array
		Players::GetTeams(name);

		//not the sexiest way of doing this, but functional
		string team1 = "1," + std::to_string(newPlayer.storedTeams[0]._Characters[0].type) + "," + std::to_string(newPlayer.storedTeams[0]._Characters[1].type) + "," + std::to_string(newPlayer.storedTeams[0]._Characters[2].type) + "/";
		string team2 = "2," + std::to_string(newPlayer.storedTeams[1]._Characters[0].type) + "," + std::to_string(newPlayer.storedTeams[1]._Characters[1].type) + "," + std::to_string(newPlayer.storedTeams[1]._Characters[2].type) + "/";
		string team3 = "3," + std::to_string(newPlayer.storedTeams[2]._Characters[0].type) + "," + std::to_string(newPlayer.storedTeams[2]._Characters[1].type) + "," + std::to_string(newPlayer.storedTeams[2]._Characters[2].type) + "/";


		return "l/l/true/" + team1 + team2 + team3;
	}
	else
	{
		return "l/l/false/";
	}
}
bool Login::ConfirmUser(std::string name, std::string pass)
{
	bool found = false;
	
	string test = name + " " + Encrypt(pass);
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

	//close file
	loginInfo.close();

	return found;
}

string Login::CreateNewUser(string name, string pass)
{
	

	bool nPass = false;//controls name loop



		while (!nPass) // step 1: get and check name
		{
			bool nameGood = true; // assumes the name will be original
			string line;

			//open file for reading
			loginInfo.open("loginInfo.txt");

			//check for existing username
			while (getline(loginInfo, line) && nameGood == true)
			{
				//if found name already exists
				if (line.find(name) == 0)
				{
					nameGood = false;
					return "l/r/false/nameTaken";
				}
			}

			loginInfo.close();

			if (nameGood) //Woo!
			{
				nPass = true;
			}
		}

		//name and pass check out, create new user
		if (nPass)
		{
			//open file for writing and append to end
			loginInfo.open("loginInfo.txt", ios::app);
			
			//NEW
			string newPass = Encrypt(newPass);
			
			//this may enter info weirdly, keep an eye...
			loginInfo << name << " " << newPass << endl;

			loginInfo.close();
			
			return "l/r/true/";
		}
	}

bool Login::CheckConnection()
{
	//this may not even be needed, can we just check inactivity while monitoring for incoming?
	return true;
}

string Login::Encrypt(string str)
{
	// Make sure the key is at least as long as the message
	string key = "J";
	string tmp = "F";

	while (key.size() < str.size())
		key += tmp;

	// And now for the encryption part
	for (int i = 0; i < str.size(); ++i) // odd that i++ breaks it...
		str[i] ^= key[i];

	return str;
}


