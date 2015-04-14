#pragma once
#include "Character.h"
class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();
	// Detect if a player is nearby.
	void detect();
};

