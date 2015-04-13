//Author:	Nicholas Higa
//Date:		4/13/2015

#pragma once

#include "Character.h"

class Rogue : public Character
{
	Rogue(char *spritePath, int row, int col, SDL_Renderer *ren) 
		: Character(spritePath, row, col, 50, 10, 4, 3, 1, 5, 0, 1, 0, ren) {}
};