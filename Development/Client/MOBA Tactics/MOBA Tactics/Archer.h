//Author:	Nicholas Higa, Michael DiFranco
//Date:		4/13/2015, 4/22/2015

#pragma once

#include "Character.h"

class Archer : public Character
{
public:
	Archer(char *spritePath, int row, int col, SDL_Renderer *ren)
		: Character(spritePath, row, col, 70, 10, 6, 5, 4, 2, 0, 1, 0, ren) {}

	void SpecialAbility(Character* target);

};