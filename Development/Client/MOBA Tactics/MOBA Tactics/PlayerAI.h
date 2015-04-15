//Author:	Nicholas Higa
//Date:		4/14/2015(NH),	4/15/2015(NH)

#pragma once

#include "ClientAPI.h"
#include "Enemy.h"
#include <vector>

class PlayerAI
{
public:
	PlayerAI();

	void AttackPhase();
	void Update();

	void AddCharacter(Enemy*);
	void StartTurn();
	void EndTurn();
	void CycleToNextCharacter();
	void RemoveCurrentActiveChar();

	bool IsATargetInAttackRange(Enemy *enemy);
	vec2 GetAttackTargetLocation(Enemy *enemy);

	bool GetIsCharacterSelected();
	vector<Enemy *> GetCharacterList();
	Enemy* GetCurrentActiveChar();

	void SetIsCharacterSelected(bool);
	void SetCurrentActiveChar(int);
	void SetCurrentActiveChar(Enemy*);
	void SetCharacterList(vector <Enemy *>);

	bool IsCharacterInTeam(Enemy*);

	//Related to setting states
	bool GetIsAIMakingMoves();

	void SetIsAIMakingMoves(bool);

private:
	vector<Enemy *> characters;
	bool isCharacterSelected;
	int currentActiveChar;

	double attackStart;

	bool isAIMakingMoves;

	void SetCharactersToIdle();
};