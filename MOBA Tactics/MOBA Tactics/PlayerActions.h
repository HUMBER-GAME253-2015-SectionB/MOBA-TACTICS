#pragma once
#include <string>
#include "Team.h"
#include "Players.h"

class PlayerActions
{
public:
	PlayerActions(void);
	~PlayerActions(void);

std::string Defend(int id, int character);

std::string Attack(int id, int character, int x, int y);

std::string Move(int player, int character, int x, int y);

bool occupied(int x, int y);

};

