//Author:	Nicholas Higa
//Date:		4/14/2015(NH),	4/15/2015(NG)

#include "PlayerAI.h"
#include "TileMap.h"

PlayerAI::PlayerAI()
{
	SetIsAIMakingMoves(false);
}

void PlayerAI::AttackPhase()
{
	Enemy* currEnemy = GetCurrentActiveChar();
	vec2 targetLocation = currEnemy->GetAttackTargetLocation();
	currEnemy->Attack(TILEMAP->GetTileAt(targetLocation.x, targetLocation.y)->GetCharacter());
	currEnemy->SetEnemyState(EnemyState::TURN_COMPLETED);
}

void PlayerAI::Update()
{
	if (GetIsAIMakingMoves())
	{
		vector<Enemy*> chars = GetCharacterList();
		for (int i = 0; i < chars.size(); i++)
			chars[i]->Update();

		Enemy* currEnemy = GetCurrentActiveChar();
		if (currEnemy->GetEnemyState() == EnemyState::TURN_STARTED)
		{
			currEnemy->SetEnemyState(EnemyState::ATTACK_PHASE1);
		}
		else if (currEnemy->GetEnemyState() == EnemyState::ATTACK_PHASE1)
		{	
			if (currEnemy->IsATargetInAttackRange())
				AttackPhase();
			else
				currEnemy->SetEnemyState(EnemyState::MOVEMENT_PHASE);
		}
		//If a target was attacked in first phase, don't move so the enemy is still in attack range
		else if (currEnemy->GetEnemyState() == EnemyState::MOVEMENT_PHASE)
		{
			currEnemy->MovementPhase();
		}
		//If a target was already attacked, dont attack again.
		else if (currEnemy->GetEnemyState() == EnemyState::ATTACK_PHASE2)
		{
			if (currEnemy->IsATargetInAttackRange())
				AttackPhase();
			else
				currEnemy->SetEnemyState(EnemyState::TURN_COMPLETED);
		}
		else if (currEnemy->GetEnemyState() == EnemyState::TURN_COMPLETED)
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
	SetIsAIMakingMoves(true);
	SetCurrentActiveChar(0);
	vector<Enemy*> chars = GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
	{
		chars[i]->SetEnemyState(EnemyState::TURN_STARTED);
		chars[i]->ResetDefense();

		if (ClientAPI::turnNumber - chars[i]->GetDiedOnTurnNumber() >= 2
			&& !chars[i]->GetIsAlive())
			chars[i]->Respawn();
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
			SetIsAIMakingMoves(false);
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

bool PlayerAI::GetIsAIMakingMoves()
{
	return isAIMakingMoves;
}

void PlayerAI::SetIsAIMakingMoves(bool val)
{
	isAIMakingMoves = val;
}