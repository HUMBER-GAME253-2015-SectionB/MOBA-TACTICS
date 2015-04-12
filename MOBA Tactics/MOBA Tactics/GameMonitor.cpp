/*
//James Finnie
Last Updated 04/11
*/

#include "GameMonitor.h"


GameMonitor::GameMonitor(void)
{
}


GameMonitor::~GameMonitor(void)
{
}

GameMonitor::GameMonitor(int client1, int client2)
{
	Team team1; /*= get active clients team*/
	Team team2; /*= get active clients team*/

	if(CheckWinner(team1, team2))
	{
		//we're outta here!
	}

	//check for any change to team status
	HealthCheck(team1);
	HealthCheck(team2);

	ActionCheck(team1);
	ActionCheck(team2);
	
	if(EndTurn(team1)) // should only fire as soon as they run out of AP...
	{
		StartTurn(team2);
	}

	if(EndTurn(team2)) // should only fire as soon as they run out of AP...
	{
		//mob update
		//endRound update - update points for holding location if appplicable
		StartTurn(team1); // this will have to go if we get mobs in, move if not
	}
	
}

bool GameMonitor::CheckWinner(Team team1, Team team2)
{
	if (team1._Score == 1000)
	{
		//declare team1 the winner

		return true;
	}
	else if (team2._Score == 1000)
	{
		//declare team2 the winner

		return true;
	}
	else
	{
		return false;
	}
}
bool GameMonitor::EndTurn(Team team)
{
	//if the game still thinks its their tuen bt no characters can act
	if (!team._Wait && !team._Characters[0].active && !team._Characters[1].active && !team._Characters[2].active)
	{
		//end turn
		team._Wait = true;
		return true;
	}
	else
	{
		//still their turn
		return false;
	}
}

void GameMonitor::StartTurn(Team team)
{
	for(int i = 0; i < 3; i++)
	{
		if(team._Characters[i].alive)
		{
			//reset stats
			team._Characters[i].curAP = team._Characters[i].maxAP;
			team._Characters[i].currDef = team._Characters[i].maxDef;
			team._Characters[i].active = true;
		}
		else //they're dead and waiting to respawn
		{
			//decrement respawn counter
			team._Characters[i].respawnTimer -= 1;
			
			//if counter hits zero, respawn at beginning, set to active/alive etc
			if(team._Characters[i].respawnTimer == 0)
			{
				//reset stats
				team._Characters[i].curHP = team._Characters[i].maxHP;
				team._Characters[i].currDef = team._Characters[i].maxDef;
				team._Characters[i].curAP = team._Characters[i].maxAP;
				//reset states
				team._Characters[i].alive = true;
				team._Characters[i].active = true;

				//reset pos //no idea how we're handling movement/position
				//update player
			}

		}
	}
	//Go!
	team._Wait = false;
}

//checking/setting alive state // move to be part of atk?
void HealthCheck(Team team) // this should be firing often enough to update at the proper times 
{
	for(int i = 0; i < 3; i++)
	{
		if(team._Characters[i].alive && team._Characters[i].curHP <= 0)
		{
			//kill em
			team._Characters[i].alive = false;
			team._Characters[i].respawnTimer = 3;

			//notify next of kin (or the players)

		}
		
	}
}

//checking/setting active states
void ActionCheck(Team team)
{
		for(int i = 0; i < 3; i++)
	{
		if(team._Characters[i].active && team._Characters[i].curAP <= 0)
		{
			//time out!	
			team._Characters[i].active = false;
		}
		
	}
}

