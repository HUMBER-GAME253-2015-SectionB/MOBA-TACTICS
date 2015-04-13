//Author:	Nicholas Higa
//Date:		4/13/2015

#pragma once

#include "Character.h"

class Warrior : public Character
{
public:
	Warrior(char *spritePath, int row, int col, SDL_Renderer *ren)
		: Character(spritePath, row, col, 100, 10, 7, 5, 1, 1, 0, 1, 0, ren) {}
};