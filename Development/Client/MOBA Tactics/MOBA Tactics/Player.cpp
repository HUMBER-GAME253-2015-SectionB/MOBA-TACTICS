//Author:	Nicholas Higa
//Date:		4/9/2015 (NH),	4/12/2015(NH)

#include "Player.h"

Player::Player() {}

void Player::AddCharacter(Character* character)
{
	characters.push_back(character);
}

void Player::StartTurn()
{
	SetIsCharacterSelected(false);
	vector<Character*> chars = GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
	{
		if (chars[i]->GetCharacterState() == CharacterState::DEFENDING)
			chars[i]->SetCharacterState(CharacterState::IDLE);
		chars[i]->ResetDefense();
	}
}

void Player::EndTurn()
{
	SetIsCharacterSelected(false);
	SetCharactersToIdle();
	vector<Character*> chars = GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
		chars[i]->ResetActionPoints();
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
	SetCharactersToIdle();

	if (GetCharacterList()[val]->GetCharacterState() != CharacterState::DEFENDING)
		GetCharacterList()[val]->SetCharacterState(CharacterState::SELECTED);
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
		SetCharactersToIdle();
		if (GetCharacterList()[i]->GetCharacterState() != CharacterState::DEFENDING)
			GetCharacterList()[i]->SetCharacterState(CharacterState::SELECTED);
	}
}

void Player::SetCharacterList(vector <Character *> val)
{
	characters = val;
}

void Player::SetCharactersToIdle()
{
	vector<Character*> chars = GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
	{
		if (chars[i]->GetCharacterState() != CharacterState::DEFENDING)
			chars[i]->SetCharacterState(CharacterState::IDLE);
	}
}

bool Player::IsCharacterInTeam(Character* _character)
{
	vector<Character*> chars = GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
	{
		if (chars[i] == _character)
			return true;
	}
	return false;
}

