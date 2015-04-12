//Author:	Nicholas Higa
//Date:		4/9/2015(NH),	4/12/2015(NH)

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
	void RemoveCurrentActiveChar();

	bool GetIsCharacterSelected();
	vector<Character *> GetCharacterList();
	Character* GetCurrentActiveChar();

	void SetIsCharacterSelected(bool);
	void SetCurrentActiveChar(int);
	void SetCurrentActiveChar(Character*);
	void SetCharacterList(vector <Character *>);

	bool IsCharacterInTeam(Character*);

private: 
	vector<Character *> characters;
	bool isCharacterSelected; 
	int currentActiveChar;

	void SetCharactersToIdle();
};