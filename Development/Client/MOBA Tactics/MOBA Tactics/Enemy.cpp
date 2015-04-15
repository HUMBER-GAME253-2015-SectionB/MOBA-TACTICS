//Author:	Nicholas Higa
//Date:		4/14/2015

#pragma once

#include "Enemy.h"

Enemy::Enemy(char *spritePath, int row, int col, SDL_Renderer *ren)
: Character(spritePath, row, col, 50, 10, 4, 3, 1, 5, 0, 1, 0, ren)
{
	pathIndex = 2;
	movingUp = true;
}

Enemy::Enemy(char *spritePath, int row, int col, int _maxHealth, int _actionPoints,
	int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren) 
	: Character(spritePath, row, col, _maxHealth, _actionPoints, _attackPower, _defense, _range, _speed, _experience, _level, _skillPoints, ren)
{
	pathIndex = 2;
	movingUp = true;
}

vector<vec2> Enemy::GetRoamingPath()
{
	return roamingPath;
}

void Enemy::SetRoamingPath(vector<vec2> path)
{
	roamingPath = path;
}

void Enemy::MovementPhase()
{
	int size = roamingPath.size();
	vec2 targetPosition;

	if (size > 0)
	{
		if (movingUp)
		{
			if (pathIndex + 1 < size)
				targetPosition = roamingPath[++pathIndex];
			else
			{
				targetPosition = roamingPath[--pathIndex];
				movingUp = false;
			}
		}
		else
		{
			if (pathIndex - 1 >= 0)
				targetPosition = roamingPath[--pathIndex];
			else
			{
				targetPosition = roamingPath[++pathIndex];
				movingUp = true;
			}
		}

		Move(targetPosition.x, targetPosition.y);
	}
	else
	{
		SetCharacterState(CharacterState::SELECTED);
	}
}

//Assumes path is on 1 axis
void Enemy::BuildRoamingPath(vec2 start, vec2 end)
{
	vector<vec2> path;
	if ((int)start.x == (int)end.x)
	{
		if (start.y < end.y)
		{
			for (int i = start.y; i <= end.y; i++)
				path.push_back(vec2(start.x, i));
		}
		else
		{
			for (int i = start.y; i >= end.y; i--)
				path.push_back(vec2(start.x, i));
		}
	}
	else
	{
		if (start.x < end.x)
		{
			for (int i = start.x; i <= end.x; i++)
				path.push_back(vec2(i, start.y));
		}
		else
		{
			for (int i = start.x; i >= end.x; i--)
				path.push_back(vec2(i, start.y));
		}
	}
	SetRoamingPath(path);
}