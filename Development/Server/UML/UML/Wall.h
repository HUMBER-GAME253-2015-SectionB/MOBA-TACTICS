#pragma once
#include "Enemy.h"
class Wall :
	public Enemy
{
public:
	Wall();
	~Wall();
	// Remove the wall once it has been destroyed.
	void destroyed();
};

