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


	//tracked in game
	int curHP;
	int curDef;
	int curAP;

	int posX;
	int posY;

	bool active; 
	bool alive; 

	//fixed at start
	int atk;
	int maxHP;
	int maxAP;
	int maxDef;

	int startX;
	int startY;

	int respawnTimer;

	int Stats[3];
};

