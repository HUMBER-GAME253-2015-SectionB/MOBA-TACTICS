//Author:	Nicholas Higa
//Date:		4/14/2015(NG)

#include "PlayerAI.h"

PlayerAI::PlayerAI()
{
	isAIMakingMoves = false;
}

void PlayerAI::MovementPhase()
{
	vector<Enemy*> chars = GetCharacterList();
}

void PlayerAI::AttackPhase()
{

}

void PlayerAI::Update()
{
	if (isAIMakingMoves)
	{
		vector<Enemy*> chars = GetCharacterList();
		for (int i = 0; i < chars.size(); i++)
			chars[i]->Update();

		Enemy* currEnemy = GetCurrentActiveChar();
		if (currEnemy->GetCharacterState() == CharacterState::IDLE)
		{
			currEnemy->MovementPhase();
		}
		else if (currEnemy->GetCharacterState() == CharacterState::SELECTED)
		{
			CycleToNextCharacter();
		}
	}
}

void PlayerAI::AddCharacter(Enemy* character)
{
	characters.push_back(character);
}

void PlayerAI::StartTurn()
{
	isAIMakingMoves = true;
	SetCurrentActiveChar(0);
	vector<Enemy*> chars = GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
	{
		if (chars[i]->GetCharacterState() == CharacterState::DEFENDING)
			chars[i]->SetCharacterState(CharacterState::IDLE);
		chars[i]->ResetDefense();
	}
}

void PlayerAI::EndTurn()
{
	SetIsCharacterSelected(false);
	SetCharactersToIdle();
	vector<Enemy*> chars = GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
		chars[i]->ResetActionPoints();
}

void PlayerAI::CycleToNextCharacter()
{
	if (GetIsCharacterSelected())
	{
		currentActiveChar++;
		if (currentActiveChar >= characters.size())
			isAIMakingMoves = false;
	}
}

void PlayerAI::RemoveCurrentActiveChar()
{
	currentActiveChar = -1;
	SetIsCharacterSelected(false);
}

bool PlayerAI::GetIsCharacterSelected()
{
	return isCharacterSelected;
}

vector<Enemy *> PlayerAI::GetCharacterList()
{
	return characters;
}

Enemy* PlayerAI::GetCurrentActiveChar()
{
	return GetCharacterList()[currentActiveChar];
}

void PlayerAI::SetIsCharacterSelected(bool val)
{
	isCharacterSelected = val;
}

void PlayerAI::SetCurrentActiveChar(int val)
{
	currentActiveChar = val;
	SetIsCharacterSelected(true);
	SetCharactersToIdle();

	if (GetCharacterList()[val]->GetCharacterState() != CharacterState::DEFENDING)
		GetCharacterList()[val]->SetCharacterState(CharacterState::SELECTED);
}

void PlayerAI::SetCurrentActiveChar(Enemy* character)
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

void PlayerAI::SetCharacterList(vector <Enemy *> val)
{
	characters = val;
}

void PlayerAI::SetCharactersToIdle()
{
	vector<Enemy*> chars = GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
	{
		if (chars[i]->GetCharacterState() != CharacterState::DEFENDING)
			chars[i]->SetCharacterState(CharacterState::IDLE);
	}
}

bool PlayerAI::IsCharacterInTeam(Enemy* _character)
{
	vector<Enemy*> chars = GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
	{
		if (chars[i] == _character)
			return true;
	}
	return false;
}

