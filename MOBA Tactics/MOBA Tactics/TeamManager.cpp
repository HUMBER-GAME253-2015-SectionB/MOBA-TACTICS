#include "TeamManager.h"
/*
//Michael Kochen, Trey Hesketh
Last Updated 03/11
*/

TeamManager::TeamManager()
{
}

TeamManager::~TeamManager()
{
}

Team TeamManager::CreateTeamWithPlayers()
{
	Team team;
	std::string cName;
	int type;
	std::string name;

	std::cout << "what is your team Name:";
	std::cin >> name; 
	team._Name = name;
	_TeamCaps.push_back(team);
	
	for (int i = 0; i < 3; i++)
	{	
		std::cout << "Characters name: ";
		std::cin >> cName;

		std::cout << "Character Type: (0)Warrior (1)Archer (2)Mage\n";
		std::cin >> type;
		if(type > 2 ){
			type = 2;
		}else if(type <0){
			type = 0;
		}else
			team._Characters.push_back(CreateCharacter(name, cName, type));
	}
	std::cout << "Your team has been created with the team name of " << name << "\n first character " << team._Characters[0].name << " : " << team._Characters[0].type << "\n second character " << team._Characters[1].name << " : " << team._Characters[1].type << "\n third character " << team._Characters[2].name << " : " << team._Characters[2].type << "\n";

	return team;
}



Team TeamManager::EditTeam(Team team)
{	
	return team;
}

void TeamManager::TeamList()
{
	_TeamCaps.begin();
	for (size_t i = 0; i < _TeamCaps.size(); i++)
	{
		std::cout << _TeamCaps[i]._Name << " ";
	}
}

void TeamManager::ChracterList()
{
	_CharCaps.begin();
	for (size_t i = 0; i < _CharCaps.size(); i++)
	{
		std::cout << _CharCaps[i].name << " ";
	}
}

void TeamManager::CreateOneCharacter(std::string TeamName)
{
	std::string cName;
	int type;

	std::cout << "What Name do you want to replace for the charcater you deleted: ";
		std::cin >> cName;

		std::cout << "Character Type: (0)Warrior (1)Archer (2)Mage\n";
		std::cin >> type;
			
		CreateCharacter(TeamName, cName, type);
}

Character TeamManager::CreateCharacter(std::string team, std::string PlayerName, int CharClass)
{
	Character character;
	character.name = PlayerName;
	character.type = CharClass;

	switch (CharClass)
	{
	case 0://Warrior
		character.Stats[0] = 15;
		character.Stats[1] = 8;
		character.Stats[2] = 3;
		break;
	case 1://Archer
		character.Stats[0] = 9;
		character.Stats[1] = 12;
		character.Stats[2] = 5;
		break;
	case 2://Mage
		character.Stats[0] = 3;
		character.Stats[1] = 7;
		character.Stats[2] = 15;
		break;
	}
	character.cTeam = team;
	_CharCaps.push_back(character);
	return character;
}

void TeamManager::DeleteTeam()
{
	std::string team;
		std::cout << "please type the team name you want to delete \n";

	std::cin >> team;
	_TeamCaps.begin();
		_CharCaps.begin();

	for (size_t i = 0; i < _TeamCaps.size(); i++)
	{
		if ( team == _TeamCaps[i]._Name)
		{			 
			for (int i = 0; i < _CharCaps.size(); i++)
			{
				if (team == _CharCaps[i].cTeam)
				{
					_CharCaps[i].name.erase();
				}
			}
			_TeamCaps[i]._Name.erase();
		}	
	}
}

void TeamManager::DeleteCharacter()
{
	bool deleted = false;
	std::string character;
	std::cout << "please type the chacter name you want to delete \n";
	std::cin >> character;

	_CharCaps.begin();
	std::string TeamName; 
	for (size_t i = 0; i < _CharCaps.size(); i++)
	{
		if ( character == _CharCaps[i].name)
		{
			TeamName = _CharCaps[i].cTeam; 
			_CharCaps[i].name.erase();
			deleted = true;
		}
	}
	if (deleted)
	{
		CreateOneCharacter(TeamName);
	}
}
