//Author:	Nicholas Higa
//Date:		3/4/2015(NH), 3/8/2015(NH), 3/10/2015(NH), 3/15/2015 (NH), 4/8/2015(NH)
#pragma once

#include "ClientAPI.h"
#include "ITileMap.h"
#include "ITile.h"
#include "ICharacter.h"
#include "Sprite.h"
#include "glm/glm.hpp"
#include <queue>

class TileMap;

using namespace glm;
using namespace std;

class Character : public ICharacter, public Sprite
{
public:
	Character();
	Character(char *spritePath, int row, int col, SDL_Renderer *ren);
	Character(char *spritePath, ITile *onTile, SDL_Renderer *ren);
	Character(char *spritePath, int row, int col, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren);
	Character(char *spritePath, ITile *onTile, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren);
	void Initialize(char *spritePath, ITile *onTile, SDL_Renderer *ren);
	void Initialize(char *spritePath, ITile *onTile, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren);
	void MoveToAdjacentTile(ITile *toTile);
	void Move(ITileMap *tileMap, ITile *toTile);
	void Move(int row, int col);
	void Attack(Character* target);
	void Defend();
	//void SpecialAbility(Ability* abilityname); Somethhing like this when special abilities are implemented, 
												//assuming new class should be created for skills.
	void ResetDefense(); //Set defense back to regular value.
	void Update();
	~Character();

	vec3 GetTileGridPosition();
	ITile *GetOnTile();

	int GetCurrenttHealth();
	int GetMaxHealth();
	int GetActionPoints();
	int GetActionPointsPerTurn();
	int GetAtackPower();
	int GetDefense();
	int GetNormalDefense();
	int GetRange();
	int GetSpeed();

	int GetExperience();
	int GetLevel();
	int GetSkillPoints();

	vec2 GetVelocity();
	bool GetIsMoving();

	void SetCurrentHealth(int num);
	void SetMaxHealth(int num);
	void SetActionPoints(int num);
	void SetActionPointsPerTurn(int num);
	void SetAttackPower(int num);
	void SetDefense(int num);
	void SetNormalDefense(int num);
	void SetRange(int num);
	void SetSpeed(int num);

	void SetExperience(int num);
	void SetLevel(int num);
	void SetSkillPoints(int num);

	void SetVelocity(vec2 vec);
	void SetIsMoving(bool _isMoving);
	
	void SetOnTile(ITile *tile);
	void SetOnTile(int row, int col);

private:
	ITile* onTile;

	int currentHealth;
	int maxHealth;
	int actionPoints;
	int actionPointsPerTurn;
	int attackPower;
	int defense;
	int normalDefense; //Defense at the start of a turn
	int range;
	int speed;

	int experience;
	int level;
	int skillPoints;

	//Methods and fields only related to moving
	ITile* GetTargetTile();
	queue<ITile *>* GetMovementPath();

	void SetTargetTile(ITile *_targetTile);
	void SetMovementPath(queue<ITile *> *_movementPath);
	void MoveToNextTile();

	bool isMoving;
	vec2 velocity;
	ITile* targetTile;
	queue<ITile *> movementPath;
};