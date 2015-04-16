#pragma once
#include <string>
#include <vector>
/*
//Michael Kochen, Marc-Antoine Lavoie
Last Updated 03/11
*/

struct NPC
{
public:

	std::string name;
	char type;

	int curHP;
	int maxHP;



	 
	int atk;

	int currDef;

	bool active; 
	bool alive; 

};
