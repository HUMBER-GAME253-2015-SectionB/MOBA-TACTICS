#pragma once
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

Team TeamManager::CreateTeamWithPlayers(int client, char whatDoesItStartWith, char whatDoesItStartWith2, char whatDoesItStartWith3)
{


	Team team;
	team._TeamNumber = client;
	team._Number.push_back(team._Number.size() + 1);

	int key = team._Number.size() + 1;

	team._Characters.push_back(CreateCharacter(client, key, whatDoesItStartWith));
	team._Characters.push_back(CreateCharacter(client, key, whatDoesItStartWith2));
	team._Characters.push_back(CreateCharacter(client, key, whatDoesItStartWith3));

	return team;

	
}



Character TeamManager::CreateCharacter(int client ,int team,  char CharClass)
{
	Character character;
	character.type = CharClass;

	switch (CharClass)
	{
	case 'w': case 'W' ://Warrior
		character.Stats[0] = 15;
		character.Stats[1] = 8;
		character.Stats[2] = 3;
		break;
	case 'a': case 'A'://Archer
		character.Stats[0] = 9;
		character.Stats[1] = 12;
		character.Stats[2] = 5;
		break;
	case 'm': case 'M' ://Mage
		character.Stats[0] = 3;
		character.Stats[1] = 7;
		character.Stats[2] = 15;
		break;
	}
	//character.cTeam = key; 
	_CharCaps.push_back(character);
	return character;
}

void TeamManager::DeleteTeam(int clintNumber, int number)
{
//loop active clinets

//if clinet == correct one 

//get user user name 

//send user name and number 
}

// void TeamManager::DeleteCharacter()
// {
// 	bool deleted = false;
// 	std::string character;
// 	std::cout << "please type the chacter name you want to delete \n";
// 	std::cin >> character;
// 
// 	_CharCaps.begin();
// 	std::string TeamName; 
// 	for (size_t i = 0; i < _CharCaps.size(); i++)
// 	{
// 		if ( character == _CharCaps[i].name)
// 		{
// 			TeamName = _CharCaps[i].cTeam; 
// 			_CharCaps[i].name.erase();
// 			deleted = true;
// 		}
// 	}
// 	if (deleted)
// 	{
// 		CreateOneCharacter(TeamName);
// 	}
// }