//Author:	Nicholas Higa
//Date:		4/13/2015

#pragma once

#include "Character.h"

class Archer : public Character
{
	Archer(char *spritePath, int row, int col, SDL_Renderer *ren)
		: Character(spritePath, row, col, 70, 10, 6, 5, 4, 2, 0, 1, 0, ren) {}
};