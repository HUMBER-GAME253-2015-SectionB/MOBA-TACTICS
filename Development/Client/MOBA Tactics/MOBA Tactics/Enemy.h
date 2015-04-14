//Author:	Nicholas Higa
//Date:		4/14/2015

#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(char *spritePath, int row, int col, SDL_Renderer *ren)
		: Character(spritePath, row, col, 50, 10, 4, 3, 1, 5, 0, 1, 0, ren) {}

	Enemy(char *spritePath, int row, int col, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren)
		: Character(spritePath, row, col, _maxHealth, _actionPoints, _attackPower, _defense, _range, _speed, _experience, _level, _skillPoints, ren) {}
};