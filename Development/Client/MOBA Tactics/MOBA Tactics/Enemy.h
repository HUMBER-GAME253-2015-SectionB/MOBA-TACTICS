//Author:	Nicholas Higa
//Date:		4/14/2015,	4/15/2015(NG)

#pragma once

#include "Character.h"
#include "ClientAPI.h"
#include "EnemyState.h"

class Enemy : public Character
{
public:
	Enemy(char *spritePath, int row, int col, SDL_Renderer *ren);

	Enemy(char *spritePath, int row, int col, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren);

	vector<vec2> GetRoamingPath();
	void SetRoamingPath(vector<vec2>);

	bool IsATargetInAttackRange();
	vec2 GetAttackTargetLocation();

	void AttackPhase();
	void MovementPhase();
	void BuildRoamingPath(vec2 start, vec2 end);

	EnemyState GetEnemyState();
	void SetEnemyState(EnemyState);

	void Update();

private:
	vector<vec2> roamingPath;
	bool movingUp;
	int pathIndex;
	EnemyState enemyState;
};