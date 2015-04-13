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
	static void CreateTeam(int client, char one, char two, char three);

	//Change an old team
	static void EditTeam(int client, int team, char one, char two, char three);

	//Create a new Character
	static Character CreateCharacter(char typem);

	//Clean up
	static void DeleteTeam(int team);

private: 

	//Team Object holder
	static std::vector<Team> _TeamCaps;

	//Character object holder
	static std::vector<Character> _CharCaps;

};

