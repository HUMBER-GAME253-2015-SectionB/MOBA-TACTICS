#include "Player.h"

Player::Player() {}

void Player::AddCharacter(Character* character)
{
	characters.push_back(character);
}

void Player::StartTurn()
{
	SetIsCharacterSelected(false);
}

void Player::EndTurn()
{
	SetIsCharacterSelected(false);
}

void Player::CycleToNextCharacter()
{
	if (GetIsCharacterSelected())
	{
		characters[currentActiveChar]->SetIsSelected(false);
		currentActiveChar++;
		currentActiveChar %= characters.size();
		characters[currentActiveChar]->SetIsSelected(true);
	}	
}

bool Player::GetIsCharacterSelected()
{
	return isCharacterSelected;
}

vector<Character *> Player::GetCharacterList()
{
	return characters;
}

int Player::GetCurrentActiveChar()
{
	return currentActiveChar;
}

void Player::SetIsCharacterSelected(bool val)
{
	isCharacterSelected = val;
}

void Player::SetCurrentActiveChar(int val)
{
	currentActiveChar = val;
	SetIsCharacterSelected(true);
}

//Test
void Player::SetCurrentActiveChar(Character* character)
{
	int i = 0;
	while (GetCharacterList()[i] != character)
		i++;

	currentActiveChar = i;
	SetIsCharacterSelected(true);
}

void Player::SetCharacterList(vector <Character *> val)
{
	characters = val;
}