#pragma once
#include "Enemy.h"
class Moving :
	public Enemy
{
public:
	Moving();
	~Moving();
	// Attack a player once in range
	void attack();
	// Move character on pre-determined path.
	void move();
};

