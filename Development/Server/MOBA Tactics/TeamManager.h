#pragma once
#include "Team.h"
#include <vector>
#include <iostream>
#include <string>
/*
//Michael Kochen, Trey Hesketh
Last Updated 03/11
*/
class TeamManager
{
public:
	TeamManager();
	~TeamManager();

	//Create new Team
	Team CreateTeam(std::string name);

	//Create Completely new Team (new characters)
	Team CreateTeamWithPlayers(int client, char whatDoesItStartWith, char whatDoesItStartWith2, char whatDoesItStartWith3);

	//Create new player when you delete one
	void CreateOneCharacter(std::string TeamName);

	//Change an old team
	Team EditTeam(Team team);

	//TeamList
	void TeamList();

	//Create a new Character
	Character CreateCharacter(int client ,int team,  char CharClass);

	//Edit an old Character
	Character EditCharacter(Character character);

	//Character List
	void ChracterList();

	//Clean up
	void DeleteTeam(int clintNumber, int number);
	void DeleteCharacter();

private: 

	//Team Object holder
	std::vector<Team> _TeamCaps;

	//Character object holder
	std::vector<Character> _CharCaps;

};

