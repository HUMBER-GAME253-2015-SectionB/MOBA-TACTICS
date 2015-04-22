
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

bool PlayerActions::occupied(int x, int y)
{
	for (int i = 0; i < 3; i++)
	{
		if (x == monitor.players[0].activeTeam._Characters[i].posX && y == monitor.players[0].activeTeam._Characters[i].posY)
		{
			return true;
		}
		if (x == monitor.players[1].activeTeam._Characters[i].posX && y == monitor.players[1].activeTeam._Characters[i].posY)
		{
			return true;
		}
	}
	for (int j = 0; j < monitor.npc.size(); j++)
	{
		if (x == monitor.npc[j].posX && y == monitor.npc[j].posY)
		{
			return true;
		}
	}
	return false;
}

std::string PlayerActions::Move(int player, int character, int x, int y)
{
	if (occupied(x, y))
		return "g/m/false/";

	Player p = Players::FindPlayerByID(player);

	int Xap = abs(p.activeTeam._Characters[character].posX - x);
	int Yap = abs(p.activeTeam._Characters[character].posY - y);

	p.activeTeam._Characters[character].posX = x;
	p.activeTeam._Characters[character].posY = y;

	p.activeTeam._Characters[character].curAP -= Xap + Yap;

	std::string newAP = "" + std::to_string(x) + "," + std::to_string(y) + "/" + std::to_string(p.activeTeam._Characters[character].curAP);

	return "g/m/" + newAP + "/";
}
