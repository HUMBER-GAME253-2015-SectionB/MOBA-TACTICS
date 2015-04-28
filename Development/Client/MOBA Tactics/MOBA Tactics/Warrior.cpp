//Author: Michael DiFranco
//Date: 4/23/2015 (MD)

#include "Warrior.h"

void Warrior::SpecialAbility(Character* target)
{
	SetCharacterState(CharacterState::ATTACKING);
	Ability* abl = new Ability(this, CRITICAL_STRIKE);

	SetCurrentActionPoints(GetCurrentActionPoints() - abl->getAPCost());
	int targetDefense = target->GetDefense();
	int atk = abl->getAttackPower();
	int damage = atk - targetDefense;

	if (damage < 1)
		damage = 1;

	target->SetCurrentHealth(target->GetCurrentHealth() - damage);
	//Check for if target dead.
	if (target->GetCurrentHealth() <= 0)
	{
		target->SetIsAlive(false);
		target->GetOnTile()->SetCharacter(NULL);
		target->SetDiedOnTurnNumber(ClientAPI::turnNumber);
	}

	float experienceGained;
	int targetLevel = target->GetLevel();
	int charLevel = GetLevel();

	//IF the target slain has a higher level gain more experience than slaying a lower level
	if (targetLevel >= charLevel)
		experienceGained = (targetLevel - charLevel) * 1000.0f + 500.0f;
	else
		experienceGained = 1.0f / (charLevel - targetLevel) * 1000.0f + 500.0f;

	SetExperience(GetExperience() + (int)experienceGained);
	SetCharacterState(CharacterState::SELECTED);
}