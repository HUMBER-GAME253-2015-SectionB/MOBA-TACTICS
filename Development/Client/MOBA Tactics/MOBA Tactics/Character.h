//Author:	Nicholas Higa, Michael DiFranco
//Date:		3/4/2015(NH), 3/8/2015(NH), 3/10/2015(NH), 3/15/2015 (NH), 4/8/2015(NH)
//			4/9/2015(NH), 4/11/2015(NH), 4/12/2015(NH), 4/22/2015(MD)

#pragma once

#include "ClientAPI.h"
#include "ITileMap.h"
#include "ITile.h"
#include "ICharacter.h"
#include "Sprite.h"
#include "glm/glm.hpp"
#include <queue>
#include <vector>
#include "CharacterState.h"
#include "Ability.h"

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
	virtual void SpecialAbility(Character* target);  //Somethhing like this when special abilities are implemented, 
												//assuming new class should be created for skills.
	void ResetDefense(); //Set defense back to regular value.
	void ResetActionPoints();

	void LevelUp();
	void Respawn();
	void RespawnAt(vec2);

	void Draw(vec2 pos, SDL_Renderer *ren);
	void Draw(SDL_Renderer*);
	void Update();
	~Character();
	
	vec2 GetSpawnLocation();
	bool GetIsAlive();
	int GetDiedOnTurnNumber();

	vec2 GetTileGridPositionVec2();
	vec3 GetTileGridPositionVec3();
	ITile *GetOnTile();

	int GetCurrentHealth();
	int GetMaxHealth();
	int GetCurrentActionPoints();
	int GetMaxActionPoints();
	int GetAtackPower();
	int GetDefense();
	int GetNormalDefense();
	int GetRange();
	int GetSpeed();

	int GetExperience();
	int GetLevel();
	int GetSkillPoints();

	vec2 GetVelocity();
	CharacterState GetCharacterState();
	CharacterState GetPrevCharacterState();

	void SetSpawnLocation(vec2);
	void SetIsAlive(bool);
	void SetDiedOnTurnNumber(int);

	void SetCurrentHealth(int num);
	void SetMaxHealth(int num);
	void SetCurrentActionPoints(int num);
	void SetMaxActionPoints(int num);
	void SetAttackPower(int num);
	void SetDefense(int num);
	void SetNormalDefense(int num);
	void SetRange(int num);
	void SetSpeed(int num);

	void SetExperience(int num);
	void SetLevel(int num);
	void SetSkillPoints(int num);

	void SetVelocity(vec2 vec);
	void SetCharacterState(CharacterState);
	void SetPrevCharacterState(CharacterState);
	
	void SetOnTile(ITile *tile);
	void SetOnTile(int row, int col);

	bool IsTileInMovementRange(vec2);
	bool IsTileInAttackRange(vec2);

	//Methods related to printing menu
	void PrintMenu();
	void PrintStats();

	//Methods and fields related to showing movement/attack range
	vector<vec2> GetMovementTiles();
	vector<vec2> GetAttackTiles();

private:
	ITile* onTile;

	int currentHealth;
	int maxHealth;
	int currentActionPoints;
	int maxActionPoints;
	int attackPower;
	int defense;
	int normalDefense; //Defense at the start of a turn
	int range;
	int speed;

	int experience;
	int level;
	int skillPoints;

	bool isAlive;
	vec2 spawnLocation;
	int diedOnTurnNumber;

	CharacterState characterState;
	CharacterState prevCharacterState;

	//Methods and fields only related to moving
	ITile* GetTargetTile();
	queue<ITile *>* GetMovementPath();

	void SetTargetTile(ITile *_targetTile);
	void SetMovementPath(queue<ITile *> *_movementPath);
	void MoveToNextTile();

	vec2 velocity;
	ITile* targetTile;
	queue<ITile *> movementPath;

	void SetMovementTiles(vector<vec2>);
	void SetAttackTiles(vector<vec2>);

	vector<vec2> GetTilesWithinRange(int);
	void UpdateMovementTiles();
	void UpdateAttackTiles();
	bool IsValidTile(vec2);
	bool IsTileInList(vec2, vector<vec2>);

	vector<vec2> movementTiles;
	vector<vec2> attackTiles;

	void AddItemToMenu(vector<char*>&, char*);
};