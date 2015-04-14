#include "TeamManager.h"
/*
//Michael Kochen, Trey Hesketh
Last Updated 03/11
*/

TeamManager::TeamManager()
{
}

TeamManager::~TeamManager()
{
}

void TeamManager::CreateTeam(int client, char one, char two, char three)
{
	Team team;
	char type[3] {one, two, three};

	_TeamCaps.push_back(team);
	
	for (int i = 0; i < 3; i++)
	{	
		team._Characters.push_back(CreateCharacter(type[i]));
	}
	//save team to database
	//function saveTeam(team);
}

void TeamManager::EditTeam(int client, int team, char one, char two, char three)
{	
	DeleteTeam(team);
	CreateTeam(client, one, two, three);
}

Character TeamManager::CreateCharacter(char CharClass)
{
	Character character;
	character.type = CharClass;

	switch (CharClass)
	{
	case 'w': case 'W'://Warrior
		character.Stats[0] = 15;
		character.Stats[1] = 8;
		character.Stats[2] = 3;
		break;
	case 'a': case 'A'://Archer
		character.Stats[0] = 9;
		character.Stats[1] = 12;
		character.Stats[2] = 5;
		break;
	case 'm': case 'M'://Mage
		character.Stats[0] = 3;
		character.Stats[1] = 7;
		character.Stats[2] = 15;
		break;
	}
	_CharCaps.push_back(character);
	return character;
}

void TeamManager::DeleteTeam(int team)
{
	_TeamCaps.begin();
	_CharCaps.begin();

	for (size_t i = 0; i < _TeamCaps.size(); i++)
	{
		if (team == i)
		{			 
			for (int ii = 0; ii < _CharCaps.size(); ii++)
			{
				_TeamCaps[ii]._Characters.clear();
			}
		}	
	}
}
