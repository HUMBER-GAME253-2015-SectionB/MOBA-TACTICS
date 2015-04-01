#pragma once

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
	bool GetIsActive();
	vector<Character *> GetCharacterList();
	int GetCurrentActiveChar();

	void SetIsCharacterSelected(bool);
	void SetIsActive(bool);
	void SetCurrentActiveChar(int);
	void SetCurrentActiveChar(Character*);
	void SetCharacterList(vector <Character *>);

private: 
	vector<Character *> characters;
	bool isActive; //Is it this players turn or not?
	bool isCharacterSelected; 
	int currentActiveChar;
};