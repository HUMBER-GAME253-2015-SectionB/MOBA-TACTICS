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