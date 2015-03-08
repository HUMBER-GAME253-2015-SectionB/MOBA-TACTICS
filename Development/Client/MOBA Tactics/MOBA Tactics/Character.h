//Author:	Nicholas Higa
//Date:		3/4/2014(NH), 3/8/2014 (NH)
#pragma once

#include "ITileMap.h"
#include "ITile.h"
#include "Sprite.h"
#include "glm/glm.hpp"
#include <queue>

using namespace glm;
using namespace std;

class Character
{
public:
	Character();
	Character(char *spritePath, ITile *onTile, SDL_Renderer *ren);
	Character(char *spritePath, ITile * nTile, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren);
	void Initialize(char *spritePath, ITile *onTile, SDL_Renderer *ren);
	void Initialize(char *spritePath, ITile *onTile, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren);
	void MoveToAdjacentTile(ITile *toTile);
	void Move(ITileMap *tileMap, ITile *toTile);
	void Attack(Character* target);
	void Defend();
	//void SpecialAbility(Ability* abilityname); Somethhing like this when special abilities are implemented, 
												//assuming new class should be created for skills.
	void ResetDefense(); //Set defense back to regular value.
	void Update();
	void Draw(SDL_Renderer *ren);
	~Character();

	Sprite* GetSprite();
	vec2 GetPosition();
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

	void SetSprite(Sprite *_sprite);
	void SetPosition(vec2 pos);

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

private:
	Sprite *sprite;
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

	bool isMoving;
	vec2 velocity;
	ITile* targetTile;
	queue<ITile *> movementPath;
};