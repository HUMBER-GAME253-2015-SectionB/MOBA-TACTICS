#pragma once

#include "Texture.h"
#include "glm/glm.hpp"

using namespace glm;

class Character
{
public:
	Character();
	Character(char *texturePath, SDL_Renderer *ren);
	Character(char *texturePath, vec3 _tilePosition, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren);
	void Initialize(char *texturePath, SDL_Renderer *ren);
	void Initialize(char *texturePath, vec3 _tilePosition, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren);
	void Move(vec3 newTilePosition);
	void Move(vec2 newMapPosition);
	void Attack(Character* target);
	void Defend();
	//void SpecialAbility(Ability* abilityname); Somethhing like this when special abilities are implemented, 
												//assuming new class should be created for skills.
	void ResetDefense(); //Set defense back to regular value.
	void Update();
	void Draw(SDL_Renderer *ren);
	~Character();

	Texture* GetTexture();
	vec3 GetTilePosition();
	vec2 GetPosition();

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

	void SetTexture(Texture* _texture);
	void SetTilePosition(vec3 tilePos);
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
private:
	Texture *texture;

	vec3 tilePosition;	//Future proofing, if a character can go on 
						//different layers on the tile map. This is 
						//why it's a vec3 instead of a vec2.
	vec2 position;		//Coordinate position

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
};