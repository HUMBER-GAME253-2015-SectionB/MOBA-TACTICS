#pragma once
#include "Enemy.h"
class Stationary :
	public Enemy
{
public:
	Stationary();
	~Stationary();
	// Attack player characters when in range.
	void attack();
	// Respawn enemy after they died and a certain amount of time has passed. (not yet implemented)
	void respawn();
};

