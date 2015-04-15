//Author:	Nicholas Higa
//Date:		4/14/2015(NH)

#pragma once

#include "ClientAPI.h"
#include "Enemy.h"
#include <vector>

class PlayerAI
{
public:
	PlayerAI();

	void MovementPhase();
	void AttackPhase();
	void Update();

	void AddCharacter(Enemy*);
	void StartTurn();
	void EndTurn();
	void CycleToNextCharacter();
	void RemoveCurrentActiveChar();

	bool GetIsCharacterSelected();
	vector<Enemy *> GetCharacterList();
	Enemy* GetCurrentActiveChar();

	void SetIsCharacterSelected(bool);
	void SetCurrentActiveChar(int);
	void SetCurrentActiveChar(Enemy*);
	void SetCharacterList(vector <Enemy *>);

	bool IsCharacterInTeam(Enemy*);

	bool isAIMakingMoves;
private:
	vector<Enemy *> characters;
	bool isCharacterSelected;
	int currentActiveChar;

	void SetCharactersToIdle();
};