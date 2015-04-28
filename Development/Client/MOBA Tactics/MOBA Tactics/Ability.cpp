//Author: Michael DiFranco
//Date: 4/22/2015 (MD)

#include "Ability.h"


Ability::Ability(Character* caster, enum AbilityName ablName)
{
	if (ablName == POWER_ATTACK)
	{
		attackPower = caster->GetAtackPower();

		APCost = 5;
		int crit = rand() % 10;
		if (crit == 1)
			attackPower *= 3;
		else
			attackPower *= 2;
	}
	else if (ablName == PRECISE_SHOT)
	{
		attackPower = caster->GetAtackPower();

		APCost = 5;
		int crit = rand() % 10;
		if (crit == 1)
			attackPower *= 3;
		else
			attackPower *= 2;
	}
	else if (ablName == CRITICAL_STRIKE)
	{
		attackPower = caster->GetAtackPower();
		APCost = 5;
		int crit = rand() % 10;
		if (crit >= 7)
			attackPower *= 4;
	}
	else if (ablName == SHIELD_SMASH)
	{
		attackPower = caster->GetAtackPower() + caster->GetDefense();
		APCost = 5;
	}
}

int Ability::getAPCost()
{
	return APCost;
}

int Ability::getAttackPower()
{
	return attackPower;
}

Ability::~Ability()
{
}
