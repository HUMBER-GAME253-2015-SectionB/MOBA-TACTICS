//Author:	Nicholas Higa, Mathieu Violette
//Date:		3/4/2015(NH), 3/8/2015(NH), 3/10/2015(NH), 3/11/2015(NH), 3/17/2015(MV),
//			4/8/2015(NH), 4/9/2015(NH), 4/11/2015(NH), 4/12/2015(NH)

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
	Initialize(spritePath, onTile, 100, 5, 10, 10, 4, 1, 0, 0, 0, ren); //Can change later for balance
}

void Character::Initialize(char *spritePath, ITile *onTile, int _maxHealth, int _actionPoints,
	int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints, SDL_Renderer *ren)
{
	Sprite::Initialize(spritePath, ren, vec2(0, 0));

	SetCurrentHealth(_maxHealth);
	SetMaxHealth(_maxHealth);
	SetCurrentActionPoints(_actionPoints); 
	SetMaxActionPoints(_actionPoints);
	SetAttackPower(_attackPower);
	SetDefense(_defense);
	SetNormalDefense(_defense);
	SetRange(_range);
	SetSpeed(_speed);

	SetExperience(_experience);
	SetLevel(_level);
	SetSkillPoints(_skillPoints);
	SetOnTile(onTile);

	SetTargetTile(NULL);
	SetCharacterState(CharacterState::IDLE);
	SetPrevCharacterState(CharacterState::IDLE);
}

void Character::MoveToAdjacentTile(ITile *toTile)
{
	if (GetCharacterState() != CharacterState::MOVING)
	{
		vec2 startPos = GetOnTile()->GetPosition();
		vec2 endPos = toTile->GetPosition();
		SetCharacterState(CharacterState::MOVING);
		SetVelocity(vec2((endPos - startPos).x / 10, (endPos - startPos).y / 10));
		SetTargetTile(toTile);
	}
}

//This move function does not account for different layers or any obstacle tiles
//Needs to be improved later on assuming obstacle tiles are required later.
void Character::Move(ITileMap *tileMap, ITile *toTile)
{
	//If character is not moving already and target position is not occupied.
	//NOTE: Character state is updated to MOVING in the MoveToAdjacentTile function, putting it into this function will cause errors.
	if (GetCharacterState() != CharacterState::MOVING && toTile->GetGridPositionVec3() != GetTileGridPositionVec3() && !toTile->GetIsOccupied()
		&& IsTileInList(toTile->GetGridPositionVec2(), GetMovementTiles()))
	{
		
		GetOnTile()->SetCharacter(NULL);
		vec3 gridDisplacement;
		vec3 tileGridPos = GetTileGridPositionVec3();
		gridDisplacement = toTile->GetGridPositionVec3() - tileGridPos;
		vec2 increment;

		vec2 currentPosition = GetTileGridPositionVec2();
		vec2 targetDestination = toTile->GetGridPositionVec2();
		int consumedAP = abs(currentPosition.x - targetDestination.x) + abs(currentPosition.y - targetDestination.y);
		SetCurrentActionPoints(GetCurrentActionPoints() - consumedAP);

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
				movementPath.push(tileMap->GetTileAt((int)tileGridPos.x, (int)toTile->GetGridPositionVec3().y, (int)tileGridPos.z + (i + 1) * (int)increment.y));
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
				movementPath.push(tileMap->GetTileAt((int)tileGridPos.x, (int)tileGridPos.y + (i + 1) * (int)increment.x, (int)toTile->GetGridPositionVec3().z));
			}
		}

		//Move to first adjacent tile in the queue.
		MoveToAdjacentTile(movementPath.front());
		movementPath.pop();
	}
}

//NOTE: Character state is updated to MOVING in the MoveToAdjacentTile function, putting it into this function will cause errors.
void Character::Move(int row, int col)
{
	ITile *temp = TILEMAP->GetTileAt(1, row, col);
	Move(TILEMAP, temp);
}

void Character::Attack(Character* target)
{
	SetCharacterState(CharacterState::ATTACKING);
	SetCurrentActionPoints(GetCurrentActionPoints() - 2);
	int targetDefense = target->GetDefense();
	int atk = GetAtackPower();
	int damage = atk - defense;

	if (damage < 1)
		damage = 1;

	target->SetCurrentHealth(target->GetCurrentHealth() - damage);
	//Check for if target dead.
	SetCharacterState(CharacterState::SELECTED);
}

void Character::Defend()
{
	SetCharacterState(CharacterState::DEFENDING);
	int x = GetDefense();
	int y = GetCurrentActionPoints();
	SetDefense(GetDefense() + GetCurrentActionPoints());
	SetCurrentActionPoints(0);
}

//void SpecialAbility(Ability* abilityname); Somethhing like this when special abilities are implemented, 
//assuming new class should be created for skills.

void Character::ResetDefense()
{
	SetDefense(GetNormalDefense());
}

void Character::ResetActionPoints()
{
	SetCurrentActionPoints(GetMaxActionPoints());
}

void Character::Update()
{
	if (GetCharacterState() == CharacterState::MOVING)
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

		//SetDefense(0); Not sure why this was here, leaving it in just in case.
	}
}

Character::~Character()
{
}

vec2 Character::GetTileGridPositionVec2()
{
	return GetOnTile()->GetGridPositionVec2();
}

vec3 Character::GetTileGridPositionVec3()
{
	return GetOnTile()->GetGridPositionVec3();
}

ITile *Character::GetOnTile()
{
	return onTile;
}

int Character::GetCurrentHealth()
{
	return currentHealth;
}

int Character::GetMaxHealth()
{
	return maxHealth;
}

int Character::GetCurrentActionPoints()
{
	return currentActionPoints;
}

int Character::GetMaxActionPoints()
{
	return maxActionPoints;
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

CharacterState Character::GetCharacterState()
{
	return characterState;
}

CharacterState Character::GetPrevCharacterState()
{
	return prevCharacterState;
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

void Character::SetCurrentActionPoints(int num)
{
	currentActionPoints = num;
	if (num < 0)
		currentActionPoints = 0;
}

void Character::SetMaxActionPoints(int num)
{
	maxActionPoints = num;
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

void Character::SetCharacterState(CharacterState charState)
{
	if (charState == CharacterState::ATTACK_SELECTED || charState == CharacterState::ATTACK_CONFIRMATION)
	{
		if (GetCurrentActionPoints() >= 2)
		{
			UpdateAttackTiles();
			vector<vec2> atkRange = GetAttackTiles();
			for (int i = 0; i < atkRange.size(); i++)
				TILEMAP->GetTileAt(atkRange[i].x, atkRange[i].y)->SetIsHighlighted(true);

			SetPrevCharacterState(GetCharacterState());
			characterState = charState;
		}
	}
	else if (charState == CharacterState::MOVEMENT_SELECTED)
	{
		if (GetCurrentActionPoints() >= 1)
		{
			UpdateMovementTiles();
			vector<vec2> moveRange = GetMovementTiles();
			for (int i = 0; i < moveRange.size(); i++)
				TILEMAP->GetTileAt(moveRange[i].x, moveRange[i].y)->SetIsHighlighted(true);

			SetPrevCharacterState(GetCharacterState());
			characterState = charState;
		}
	}
	else
	{
		SetPrevCharacterState(GetCharacterState());
		characterState = charState;
	}

	if (GetPrevCharacterState() == CharacterState::MOVEMENT_SELECTED
		|| GetPrevCharacterState() == CharacterState::ATTACK_CONFIRMATION)
		TILEMAP->ResetHighlights();

	PrintMenu();
}

void Character::SetPrevCharacterState(CharacterState charState)
{
	prevCharacterState = charState;
}

void Character::PrintMenu()
{
	/*	int currentHealth;
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
	int skillPoints;*/
	
	system("cls"); //Very bad way to clear console screen, but it will be fine for this purpose.
	CharacterState tmp = GetCharacterState();
	int currAP = GetCurrentActionPoints();

	vector<char*> menu;

	if (tmp == CharacterState::IDLE)
	{

	}
	else if (tmp == CharacterState::ATTACKING)
	{

	}
	else if (tmp == CharacterState::ATTACK_SELECTED)
	{
		PrintStats();

		//printf("Click on enemy to Attack    Cost: 2 AP\n\n");
		//printf("1/M to Move                 Cost: 1 AP per tile\n");
		//printf("2/D to Defend               Cost: Consumes all AP\n");
		//printf("4/E to End turn\n");
		//printf("5/B to go Back to main menu.\n\n");
		AddItemToMenu(menu, "attack2");
		AddItemToMenu(menu, "move1");
		AddItemToMenu(menu, "defense1");
		AddItemToMenu(menu, "end");
		AddItemToMenu(menu, "back");
	}
	else if (tmp == CharacterState::ATTACK_CONFIRMATION)
	{
		PrintStats();

		//printf("Are you sure?\n");
		//printf("3/A again to confirm        Cost: 2 AP\n\n");
		//printf("1/M to Move                 Cost: 1 AP per tile\n");
		//printf("2/D to Defend               Cost: Consumes all AP\n");
		//printf("4/E to End turn\n");
		//printf("5/B to go Back to main menu.\n\n");

		AddItemToMenu(menu, "attack3");
		AddItemToMenu(menu, "move1");
		AddItemToMenu(menu, "defense1");
		AddItemToMenu(menu, "end");
		AddItemToMenu(menu, "back");
	}
	else if (tmp == CharacterState::DEFEND_SELECTED)
	{
		PrintStats();

		//printf("Are you sure?\n");
		//printf("2/D again to confirm        Cost: Consumes all AP\n\n");
		//printf("1/M to Move                 Cost: 1 AP per tile\n");
		//printf("3/A to Attack               Cost: 2 AP\n");
		//printf("4/E to End turn\n");
		//printf("5/B to go Back to main menu.\n\n");
		AddItemToMenu(menu, "defense2");
		AddItemToMenu(menu, "move1");
		AddItemToMenu(menu, "attack1");
		AddItemToMenu(menu, "end");
		AddItemToMenu(menu, "back");
	}
	else if (tmp == CharacterState::DEFENDING)
	{
		printf("Status: Defending\n\n");
		PrintStats();
		AddItemToMenu(menu, "switch");
		AddItemToMenu(menu, "end");
	}
	else if (tmp == CharacterState::MOVEMENT_SELECTED)
	{
		PrintStats();

		//printf("Click on tile to Move       Cost: 1 AP per tile\n\n");
		//printf("2/D to Defend               Cost: Consumes all AP\n");
		//printf("3/A to Attack               Cost: 2 AP\n");
		//printf("4/E to End turn\n");
		//printf("5/B to go Back to main menu.\n\n");
		AddItemToMenu(menu, "move2");
		AddItemToMenu(menu, "defense1");
		AddItemToMenu(menu, "attack1");
		AddItemToMenu(menu, "end");
		AddItemToMenu(menu, "back");
	}
	else if (tmp == CharacterState::MOVING)
	{

	}
	else if (tmp == CharacterState::SELECTED)
	{
		PrintStats();

		//printf("1/M to Move                 Cost: 1 AP per tile\n");
		//printf("2/D to Defend               Cost: Consumes all AP\n");
		//printf("3/A to Attack               Cost: 2 AP\n");
		//printf("4/E to End Turn\n\n");
		AddItemToMenu(menu, "move1");
		AddItemToMenu(menu, "defense1");
		AddItemToMenu(menu, "attack1");
		AddItemToMenu(menu, "end");

		if (menu[0] == "4/E to End turn\n")
		{
			menu.clear();
			AddItemToMenu(menu, "switch");
			AddItemToMenu(menu, "end");
		}
	}

	for (int i = 0; i < menu.size(); i++)
		printf(menu[i]);
}

void Character::PrintStats()
{
	printf("Level: %d Exp: %d\n", GetLevel(), GetExperience());
	printf("Action Points: %d/%d\n\n", GetCurrentActionPoints(), GetMaxActionPoints());
	printf("HP: %d/%d\n", GetCurrentHealth(), GetMaxHealth());
	printf("ATK: %d\n", GetAtackPower());
	printf("DEF: %d\n", GetDefense());
	printf("RNGE: %d\n", GetRange());
	printf("SPD: %d\n\n", GetSpeed());
}

void Character::AddItemToMenu(vector<char*> &menu, char* string)
{
	char* move1 = "1/M to Move                 Cost: 1 AP per tile\n";
	char* move2 = "Click on tile to Move       Cost: 1 AP per tile\n\n";
	char* atk1 = "3/A to Attack               Cost: 2 AP\n";
	char* atk2 = "Click on enemy to Attack    Cost: 2 AP\n\n";
	char* atk3 = "3/A again to confirm        Cost: 2 AP\n";
	char* def1 = "2/D to Defend               Cost: Consumes all AP\n";
	char* def3 = "2/D again to confirm        Cost: Consumes all AP\n\n";
	char* end = "4/E to End turn\n";
	char* back = "5/B to go Back to main menu.\n\n";
	char* confirm = "Are you sure?\n";
	char* switchChar = "No more AP, Switch Characters\n";
	int currActionPoints = GetCurrentActionPoints();

	if (string == "move1")
	{
		if (currActionPoints >= 1)
			menu.push_back(move1);
	}
	else if (string == "move2")
	{
		if (currActionPoints >= 1)
			menu.push_back(move2);
	}
	else if (string == "attack1")
	{
		if (currActionPoints >= 2)
			menu.push_back(atk1);
	}
	else if (string == "attack2")
	{
		if (currActionPoints >= 2)
			menu.push_back(atk2);
	}
	else if (string == "attack3")
	{
		if (currActionPoints >= 2)
		{
			menu.push_back(confirm);
			menu.push_back(atk3);
		}
	}
	else if (string == "defense1")
	{
		if (currActionPoints >= 1)
			menu.push_back(def1);
	}
	else if (string == "defense2")
	{
		if (currActionPoints >= 1)
		{
			menu.push_back(confirm);
			menu.push_back(def3);
		}
	}
	else if (string == "end")
		menu.push_back(end);
	else if (string == "back")
		menu.push_back(back);
	else if (string == "switch")
		menu.push_back(switchChar);
}

bool Character::IsTileInMovementRange(vec2 val)
{
	return IsTileInList(val, GetMovementTiles());
}

bool Character::IsTileInAttackRange(vec2 val)
{
	return IsTileInList(val, GetAttackTiles());
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
	SetCharacterState(CharacterState::SELECTED);
	SetOnTile(GetTargetTile());

	if (!GetMovementPath()->empty())
	{
		if (GetOnTile()->GetCharacter() == this)
			GetOnTile()->SetCharacter(NULL);
		MoveToAdjacentTile(movementPath.front());
		movementPath.pop();
	}

	if (GetMovementPath()->empty())
		UpdateMovementTiles();
}

//Private methods related to getting tiles.
vector<vec2> Character::GetTilesWithinRange(int value)
{
	vector<vec2> tmp;
	vector<int> xDisplacements;
	vec2 origin = GetTileGridPositionVec2();

	//Build displacements for x for inner loop
	//With origin 2,2, xDisplacements vector will be built with
	//0,1,2,1,0 which corresponds to the xDisplacement for the top
	//of each column. For example the above mentioned vector's 
	//displacement refer to the displacements from cells between
	//the origin (2,2) and points (2,0) (1,1) (0,2) (1,3) and (2,4)
	//         0,2
	//     1,1 1,2 1,3 
	// 2,0 2,1 2,2 2,3 2,4
	//     3,1 3,2 3,3
	//         4,2
	for (int i = 0; i < value * 2 + 1; i++)
	{
		if (i <= value)
			xDisplacements.push_back(i);
		else
			xDisplacements.push_back(value * 2 - i);
	}

	//Check if the vector tile is a valid tile that exists on the
	//tilemap. If it does push it onto the vector.
	for (int i = 0; i < value * 2 + 1; i++)
	{
		for (int j = -xDisplacements[i]; j <= xDisplacements[i]; j++)
		{
			vec2 checkTile = vec2(origin.x - j, origin.y + i - value);
			if (IsValidTile(checkTile))
				tmp.push_back(checkTile);
		}
	}

	return tmp;
}

void Character::UpdateMovementTiles()
{
	SetMovementTiles(GetTilesWithinRange(GetCurrentActionPoints()));
}

void Character::UpdateAttackTiles()
{
	SetAttackTiles(GetTilesWithinRange(GetRange()));
}

vector<vec2> Character::GetMovementTiles()
{
	return movementTiles;
}

vector<vec2> Character::GetAttackTiles()
{
	return attackTiles;
}

void Character::SetMovementTiles(vector<vec2> val)
{
	movementTiles = val;
}

void Character::SetAttackTiles(vector<vec2> val)
{
	attackTiles = val;
}

bool Character::IsValidTile(vec2 val)
{
	return (val.x >= 0 && val.y >= 0 && val.x < TILEMAP->GetNumWidth() - 1 && val.y < TILEMAP->GetNumHeight() - 1);
}

bool Character::IsTileInList(vec2 checkVec, vector<vec2> vecList)
{
	for (int i = 0; i < vecList.size(); i++)
	{
		if (vecList[i].x == checkVec.x && vecList[i].y == checkVec.y)
			return true;
	}
	return false;
}