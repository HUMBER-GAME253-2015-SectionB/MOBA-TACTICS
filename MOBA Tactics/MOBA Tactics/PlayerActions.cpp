#pragma once
#include "PlayerActions.h"


PlayerActions::PlayerActions(void)
{
}


PlayerActions::~PlayerActions(void)
{
}

std::string PlayerActions::Defend(Character Defender)// may require userID as well?
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

	return "char#/defending/newDef#/";
}

std::string PlayerActions::Attack(Character Attacker, int x, int y)
{
	//get value of the attacker 
	//find the object on the (x,y) 
	//find the defense of the object
	//subtract the attack by defense 
	//the remaining subtract that from the health
	
	return "targets/new/hp/";
}

bool occupied(int x, int y)
{
	for (int i = 0; i < 3; i++)
	{
		if (x == players[0]._Characters[i].posX && y == players[0]._Characters[i].posY)
		{
			return true;
		}
		if (x == players[1]._Characters[i].posX && y == players[1]._Characters[i].posY)
		{
			return true;
		}
	}
	for (int j = 0; j < npcs.size(); j++);
	{
		if (x == npcs[i].posX && y == npcs[i].posY)
		{
			return true;
		}
	}
	return false;
}

string move(int player, int character, int x, int y)
{
	if (occupied(x, y))
		return "g/m/false/";

	int Xap = abs(players[player]._Characters[character].posX - x);
	int Yap = abs(players[player]._Characters[character].posY - y);

	players[player]._Characters[character].posX = x;
	players[player]._Characters[character].posY = y;

	players[player]._Characters[character].currentAP -= Xap + Yap;
	string newAP = "" + x + "," + y + "/" + players[player]._Characters[character].currentAP;

	return "g/m/newAP/";
}
