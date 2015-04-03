#pragma once

#include "ClientAPI.h"
#include "Character.h"
#include <vector>

class Player
{
public:
	Player();
	void AddCharacter(Character*);
	void StartTurn();
	void EndTurn();
	void CycleToNextCharacter();

	bool GetIsCharacterSelected();
	vector<Character *> GetCharacterList();
	int GetCurrentActiveChar();

	void SetIsCharacterSelected(bool);
	void SetCurrentActiveChar(int);
	void SetCurrentActiveChar(Character*);
	void SetCharacterList(vector <Character *>);

private: 
	vector<Character *> characters;
	bool isCharacterSelected; 
	int currentActiveChar;
};