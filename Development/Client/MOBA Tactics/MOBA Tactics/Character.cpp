//Author:	Nicholas Higa, Mathieu Violette
//Date:		3/4/2015(NH), 3/8/2015(NH), 3/10/2015(NH), 3/11/2015(NH), 3/17/2015(MV),
//			4/8/2015(NH)

#include "Character.h"
#include <cstdlib>
#include "TileMap.h"

Character::Character()
{

}

Character::Character(char *spritePath, int row, int col, SDL_Renderer *ren)
{
	ITile *temp = TILEMAP->GetTileAt(row, col);
	Initialize(spritePath, temp, ren);
}

Character::Character(char *spritePath, ITile *onTile, SDL_Renderer *ren)
{
	Initialize(spritePath, onTile, ren);
}

Character::Character(char *spritePath, ITile *onTile, int _maxHealth, int _actionPoints,
	int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren)
{
	Initialize(spritePath, onTile, _maxHealth, _actionPoints, _attackPower, _defense, _range, _speed, _experience, _level, _skillPoints, ren);
}

Character::Character(char *spritePath, int row, int col, int _maxHealth, int _actionPoints,
	int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren)
{
	ITile *temp = TILEMAP->GetTileAt(row, col);
	Initialize(spritePath, temp, _maxHealth, _actionPoints, _attackPower, _defense, _range, _speed, _experience, _level, _skillPoints, ren);
}

void Character::Initialize(char *spritePath, ITile *onTile, SDL_Renderer *ren)
{
	Initialize(spritePath, onTile, 100, 10, 10, 10, 1, 1, 0, 0, 0, ren); //Can change later for balance
}

void Character::Initialize(char *spritePath, ITile *onTile, int _maxHealth, int _actionPoints,
	int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren)
{
	Sprite::Initialize(spritePath, ren, vec2(0, 0));

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
	SetOnTile(onTile);

	SetIsMoving(false);
	SetTargetTile(NULL);
}

void Character::MoveToAdjacentTile(ITile *toTile)
{
	if (!GetIsMoving())
	{
		vec2 startPos = GetOnTile()->GetPosition();
		vec2 endPos = toTile->GetPosition();
		SetIsMoving(true);
		SetVelocity(vec2((endPos - startPos).x / 10, (endPos - startPos).y / 10));
		SetTargetTile(toTile);
	}
}

//This move function does not account for different layers or any obstacle tiles
//Needs to be improved later on assuming obstacle tiles are required later.
void Character::Move(ITileMap *tileMap, ITile *toTile)
{
	if (!GetIsMoving() && toTile->GetGridPosition() != GetTileGridPosition() && !toTile->GetIsOccupied())
	{
		GetOnTile()->SetCharacter(NULL);
		vec3 gridDisplacement;
		vec3 tileGridPos = GetTileGridPosition();
		gridDisplacement = toTile->GetGridPosition() - tileGridPos;
		vec2 increment;

		if (gridDisplacement.y > 0)
			increment.x = 1;
		else
			increment.x = -1;

		if (gridDisplacement.z > 0)
			increment.y = 1;
		else
			increment.y = -1;

		//Random function, to randomize movement just slightly. Either the character first moves horizontally then vertically
		//or the character moves vertically then horizontally

		//Create a queue for the movement path. The queue corresponds to every tile that the character has to go through, so that
		//moveToAdjacentTile function can be used.
		if (rand() % 2)
		{
			for (int i = 0; i < abs((int)gridDisplacement.y); i++)
			{
				movementPath.push(tileMap->GetTileAt((int)tileGridPos.x, (int)tileGridPos.y + (i + 1) * (int)increment.x, (int)tileGridPos.z));
			}

			for (int i = 0; i < abs((int)gridDisplacement.z); i++)
			{
				movementPath.push(tileMap->GetTileAt((int)tileGridPos.x, (int)toTile->GetGridPosition().y, (int)tileGridPos.z + (i + 1) * (int)increment.y));
			}
		}
		else
		{
			for (int i = 0; i < abs((int)gridDisplacement.z); i++)
			{
				movementPath.push(tileMap->GetTileAt((int)tileGridPos.x, (int)tileGridPos.y, (int)tileGridPos.z + (i + 1) * (int)increment.y));
			}

			for (int i = 0; i < abs((int)gridDisplacement.y); i++)
			{
				movementPath.push(tileMap->GetTileAt((int)tileGridPos.x, (int)tileGridPos.y + (i + 1) * (int)increment.x, (int)toTile->GetGridPosition().z));
			}
		}

		//Move to first adjacent tile in the queue.
		MoveToAdjacentTile(movementPath.front());
		movementPath.pop();
	}
}

void Character::Move(int row, int col)
{
	ITile *temp = TILEMAP->GetTileAt(1, row, col);
	Move(TILEMAP, temp);
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
	if (GetIsMoving())
	{
		vec2 vel = GetVelocity();
		vec2 targetPos = GetTargetTile()->GetPosition();
		targetPos.x += GetTargetTile()->GetTileWidth() / 2 - GetWidth() / 2;
		targetPos.y -= GetHeight() / 2;

		vec2 tmp = GetPosition();
		SetPosition(tmp += GetVelocity());
		
		//I could make this the whole next if block into a single if statement if I wanted
		//to, however this way looks much cleaner and is more readable.

		//Cases moving right, down
		if (vel.x > 0 && vel.y > 0 
			&& tmp.x > targetPos.x && tmp.y > targetPos.y) 
		{
			MoveToNextTile();
		}
		//moving left, down
		else if (vel.x < 0 && vel.y > 0 && 
			tmp.x < targetPos.x && tmp.y > targetPos.y)
		{
			MoveToNextTile();
		}
		//moving up, right
		else if (vel.x > 0 && vel.y < 0 && 
			tmp.x > targetPos.x && tmp.y < targetPos.y)
		{
			MoveToNextTile();
		}
		//moving up, left
		else if (vel.x < 0 && vel.y < 0 &&
			tmp.x < targetPos.x && tmp.y < targetPos.y)
		{
			MoveToNextTile();
		}

		SetDefense(0);
	}
}

Character::~Character()
{
}

vec3 Character::GetTileGridPosition()
{
	return GetOnTile()->GetGridPosition();
}

ITile *Character::GetOnTile()
{
	return onTile;
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

vec2 Character::GetVelocity()
{
	return velocity;
}

bool Character::GetIsMoving()
{
	return isMoving;
}

void Character::SetOnTile(ITile *tile)
{
	vec2 temp;
	temp.x = tile->GetPosition().x + tile->GetTileWidth() / 2 - GetWidth() / 2;
	temp.y = tile->GetPosition().y - GetHeight() / 2;
	SetPosition(temp);
	onTile = tile;

	if (tile->GetCharacter() == NULL)
		tile->SetCharacter(this);
}

void Character::SetOnTile(int row, int col)
{
	ITile *temp = TILEMAP->GetTileAt(row, col);
	SetOnTile(temp);
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

void Character::SetVelocity(vec2 vec)
{
	velocity = vec;
}

void Character::SetIsMoving(bool _isMoving)
{
	isMoving = _isMoving;
}

//Private methods
ITile* Character::GetTargetTile()
{
	return targetTile;
}

queue<ITile *>* Character::GetMovementPath()
{
	return &movementPath;
}

void Character::SetTargetTile(ITile *_targetTile)
{
	targetTile = _targetTile;
}

void Character::SetMovementPath(queue<ITile *> *_movementPath)
{
	movementPath = *_movementPath;
}

void Character::MoveToNextTile()
{
	SetIsMoving(false);
	SetOnTile(GetTargetTile());

	if (!GetMovementPath()->empty())
	{
		if (GetOnTile()->GetCharacter() == this)
			GetOnTile()->SetCharacter(NULL);
		MoveToAdjacentTile(movementPath.front());
		movementPath.pop();
	}
}