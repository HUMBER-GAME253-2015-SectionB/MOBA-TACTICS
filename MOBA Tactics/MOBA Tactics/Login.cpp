/*
//James Finnie
Last Updated 04/07
*/

#include "stdafx.h"
#include "Login.h"
#include "Team.h"

fstream loginInfo;

Login::Login()
{
}


Login::~Login()
{
}

string Login::TryLogin(string name, string pass)
{
	if (ConfirmUser(name, pass))
	{
		//everything checks out!
		return "login/OK/Message/";
	}
	else
	{
		return "login/Fail/Message/";
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
					return "create/failed/Name/already/exists/";
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
			
			return "create/OK/everything worked";
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

string Login::Defend(Character Defender)// may require userID as well?
{


	if (Defender.currDef >= Defender.maxDef)
	{
		Defender.currDef = Defender.maxDef;

	}
	else
	{
		Defender.currDef += Defender.curAP;
		Defender.curAP = 0;
		Defender.active = false;

	}
	//how to get user info from team manager

	//add ap to currentDef
	//char[unit].currDef += char[unit].currAP;

	//clear remaining ap to be safe
	//char[unit].currAP = 0;

	//set unit to inacive
	//char[unit].active = false;

	//end turn automatically if all 3 chars are inactive?

	return "char#/defending/newDef#/if/client/doesnt/want/to/calc/it/";
}

std::string Login::Attack(Character Attacker, int x, int y)
{
	//get value of the attacker 
	//find the object on the (x,y) 
	//find the defense of the object
	//subtract the attack by defense 
	//the remaining subtract that from the health
	
	
}
