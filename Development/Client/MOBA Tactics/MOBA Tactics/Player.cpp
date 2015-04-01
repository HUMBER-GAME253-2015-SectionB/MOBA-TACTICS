#include "Player.h"

void Player::AddCharacter(Character* character)
{
	characters.push_back(character);
}

void Player::StartTurn()
{
	SetIsActive(true);
	SetIsCharacterSelected(false);
}

void Player::EndTurn()
{
	SetIsActive(false);
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

bool Player::GetIsActive()
{
	return isActive;
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

void Player::SetIsActive(bool val)
{
	isActive = val;
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