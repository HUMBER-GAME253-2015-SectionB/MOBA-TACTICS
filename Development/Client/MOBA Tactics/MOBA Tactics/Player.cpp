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
		currentActiveChar++;
		currentActiveChar %= characters.size();
	}	
}

void Player::RemoveCurrentActiveChar()
{
	currentActiveChar = -1;
	SetIsCharacterSelected(false);
}

bool Player::GetIsCharacterSelected()
{
	return isCharacterSelected;
}

vector<Character *> Player::GetCharacterList()
{
	return characters;
}

Character* Player::GetCurrentActiveChar()
{
	return GetCharacterList()[currentActiveChar];
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

void Player::SetCurrentActiveChar(Character* character)
{
	if (character == NULL)
	{
		currentActiveChar = -1;
		SetIsCharacterSelected(false);
	}
	else
	{
		int i = 0;
		while (GetCharacterList()[i] != character)
			i++;

		currentActiveChar = i;
		SetIsCharacterSelected(true);
	}
}

void Player::SetCharacterList(vector <Character *> val)
{
	characters = val;
}