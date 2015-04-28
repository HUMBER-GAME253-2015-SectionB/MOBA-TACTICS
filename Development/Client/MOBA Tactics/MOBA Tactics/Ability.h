//Author: Michael DiFranco
//Date: 4/22/2015 (MD)

#pragma once
#include "Character.h"

enum AbilityName { POWER_ATTACK, PRECISE_SHOT, SHIELD_SMASH, CRITICAL_STRIKE };

class Ability
{
public:
	Ability(Character* caster, enum AbilityName ablName);
	~Ability();

	void PowerShot();

	int getAPCost();
	int getAttackPower();

private:
	int APCost;
	int attackPower;
};

