#pragma once
#include "PlayerActions.h"


PlayerActions::PlayerActions(void)
{
}


PlayerActions::~PlayerActions(void)
{
}

std::string PlayerActions::Defend(int id, int character)// may require userID as well?
{

	Character Defender = Players::FindPlayerByID(id).activeTeam._Characters[character];

	if (Defender.curDef >= Defender.maxDef)
	{
		Defender.curDef = Defender.maxDef;

	}
	else
	{
		Defender.curDef += Defender.curAP;
		Defender.curAP = 0;
		Defender.active = false;

	}

	return "char#/defending/newDef#/";
}

std::string PlayerActions::Attack(int id, int character, int x, int y)
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
	for (int j = 0; j < npcs.size(); j++)
	{
		if (x == npcs[j].posX && y == npcs[j].posY)
		{
			return true;
		}
	}
	return false;
}

std::string Move(int player, int character, int x, int y)
{
	if (occupied(x, y))
		return "g/m/false/";

	Player p = Players::FindPlayerByID(player);

	int Xap = abs(p.activeTeam._Characters[character].posX - x);
	int Yap = abs(p.activeTeam._Characters[character].posY - y);

	p.activeTeam._Characters[character].posX = x;
	p.activeTeam._Characters[character].posY = y;

	p.activeTeam._Characters[character].curAP -= Xap + Yap;

	std::string newAP = "" + x + "," + y + "/" + p.activeTeam._Characters[character].curAP;

	return "g/m/" + newAP + "/";
}
