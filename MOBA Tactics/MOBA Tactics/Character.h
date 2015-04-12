#pragma once
#include <string>
#include <vector>
/*
//Michael Kochen, Trey Hesketh
Last Updated 03/11
*/

struct Character
{
public:

	std::string name;
	int cTeam;
	char type;

	int curHP;
	int maxHP;

	int maxAP;
	int curAP;
	 
	int akt;

	int maxDef;
	int currDef;

	bool active; 
	bool alive; 

	int respawnTimer;

	int Stats[3];
};

