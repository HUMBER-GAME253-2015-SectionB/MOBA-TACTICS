#pragma once
#include <string>
#include "Team.h"

class PlayerActions
{
public:
	PlayerActions(void);
	~PlayerActions(void);

std::string Defend(Character Defender);

std::string Attack(Character Attacker, int x, int y);

};

