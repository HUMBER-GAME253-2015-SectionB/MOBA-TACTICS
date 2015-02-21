#include "Character.h"

Character::Character()
{

}

Character::Character(char *texturePath, SDL_Renderer *ren)
{
	Initialize(texturePath, ren);
}

Character::Character(char *texturePath, vec3 _tilePosition, int _maxHealth, int _actionPoints,
	int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren)
{
	Initialize(texturePath, _tilePosition, _maxHealth, _actionPoints, _attackPower, _defense, _range, _speed, _experience, _level, _skillPoints, ren);
}

void Character::Initialize(char *texturePath, SDL_Renderer *ren)
{
	texture = new Texture();
	texture->LoadFromFile(texturePath, ren);
	Initialize(texturePath, vec3(0, 0, 0), 100, 10, 10, 10, 1, 1, 0, 0, 0, ren); //Can change later for balance
}

void Character::Initialize(char *texturePath, vec3 _tilePosition, int _maxHealth, int _actionPoints,
	int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren)
{
	texture = new Texture();
	texture->LoadFromFile(texturePath, ren);
	SetTilePosition(_tilePosition);
	SetPosition(vec2(0, 0)); //Change after

	SetCurrentHealth(_maxHealth);
	SetMaxHealth(_maxHealth);
	SetActionPoints(_actionPoints); 
	SetActionPointsPerTurn(_actionPoints);
	SetAttackPower(_attackPower);
	SetDefense(_defense);
	SetNormalDefense(_defense);
	SetRange(_range);
	SetSpeed(_speed);

	SetExperience(_experience);
	SetLevel(_level);
	SetSkillPoints(_skillPoints);
}

void Character::Move(vec3 newTilePosition)
{

}

void Character::Move(vec2 newMapPosition)
{

}

void Character::Attack(Character* target)
{

}

void Character::Defend()
{

}

//void SpecialAbility(Ability* abilityname); Somethhing like this when special abilities are implemented, 
//assuming new class should be created for skills.

void Character::ResetDefense()
{
	SetDefense(GetNormalDefense());
}

void Character::Update()
{

}

void Character::Draw(SDL_Renderer *ren)
{
	texture->Render(position.x, position.y, NULL, ren);
}

Character::~Character()
{
	delete texture;
}

Texture* Character::GetTexture()
{
	return texture;
}

vec3 Character::GetTilePosition()
{
	return tilePosition;
}

vec2 Character::GetPosition()
{
	return position;
}

int Character::GetCurrenttHealth()
{
	return currentHealth;
}

int Character::GetMaxHealth()
{
	return maxHealth;
}

int Character::GetActionPoints()
{
	return actionPoints;
}

int Character::GetActionPointsPerTurn()
{
	return actionPointsPerTurn;
}

int Character::GetAtackPower()
{
	return attackPower;
}

int Character::GetDefense()
{
	return defense;
}

int Character::GetNormalDefense()
{
	return normalDefense;
}

int Character::GetRange()
{
	return range;
}

int Character::GetSpeed()
{
	return speed;
}

int Character::GetExperience()
{
	return experience;
}

int Character::GetLevel()
{
	return level;
}

int Character::GetSkillPoints()
{
	return skillPoints;
}

void Character::SetTexture(Texture* _texture)
{
	texture = _texture;
}

void Character::SetTilePosition(vec3 tilePos)
{
	tilePosition = tilePos;
}

void Character::SetPosition(vec2 pos)
{
	position = pos;
}

void Character::SetCurrentHealth(int num)
{
	currentHealth = num;
}

void Character::SetMaxHealth(int num)
{
	maxHealth = num;
}

void Character::SetActionPoints(int num)
{
	actionPoints = num;
}

void Character::SetActionPointsPerTurn(int num)
{
	actionPointsPerTurn = num;
}

void Character::SetAttackPower(int num)
{
	attackPower = num;
}

void Character::SetDefense(int num)
{
	defense = num;
}

void Character::SetNormalDefense(int num)
{
	normalDefense = num;
}

void Character::SetRange(int num)
{
	range = num;
}

void Character::SetSpeed(int num)
{
	speed = num;
}

void Character::SetExperience(int num)
{
	experience = num;
}

void Character::SetLevel(int num)
{
	level = num;
}

void Character::SetSkillPoints(int num)
{
	skillPoints = num;
}