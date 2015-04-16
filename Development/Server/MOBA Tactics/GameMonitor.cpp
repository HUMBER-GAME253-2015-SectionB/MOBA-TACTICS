/*
//James Finnie
Last Updated 04/16
*/
#include "GameMonitor.h"


GameMonitor::GameMonitor(void)
{
}


GameMonitor::~GameMonitor(void)
{
}

GameMonitor::GameMonitor(Player player1, Player player2)
{
	Team team1 = player1.activeTeam;
	Team team2 = player2.activeTeam;

	if(CheckWinner(player1,player2))
	{
		//we're outta here!
		EndGame(player1,player2);
	}

	//check for any change to team status
	HealthCheck(team1);
	HealthCheck(team2);

	ActionCheck(team1);
	ActionCheck(team2);
	
	if(EndTurn(player1)) // should only fire as soon as they run out of AP...
	{
		StartTurn(player2);
	}

	if(EndTurn(player2)) // should only fire as soon as they run out of AP...
	{
		//mob update
		//endRound update - update points for holding location if appplicable
		StartTurn(player1); // this will have to go if we get mobs in, move if not
	}
	
}

bool GameMonitor::CheckWinner(Player player1, Player player2)
{
	if (player1.score >= 1000)
	{
		//declare team1 the winner

		return true;
	}
	else if (player2.score >= 1000)
	{
		//declare team2 the winner

		return true;
	}
	else
	{
		return false;
	}
}
bool GameMonitor::EndTurn(Player player)
{
	Team team = player.activeTeam;

	//if the game still thinks its their tuen bt no characters can act
	if (!player.wait && !team._Characters[0].active && !team._Characters[1].active && !team._Characters[2].active)
	{
		//end turn
		player.wait = true;
		//notfiy player
		return true;
	}
	else
	{
		//still their turn
		return false;
	}
}

void GameMonitor::StartTurn(Player player)
{
	Team team = player.activeTeam;

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

				//reset pos 
				//update players
			}

		}
	}
	//Go!
	player.wait = false;
	//notify player
}

//checking/setting alive state // move to be part of atk?
void GameMonitor::HealthCheck(Team team) // this should be firing often enough to update at the proper times 
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
void GameMonitor::ActionCheck(Team team)
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

	void GameMonitor::StartGame(Player player1, Team team1, Player player2, Team team2) //may send just an int and we grab from storedTeams arr
	{
		//assign active team
		player1.activeTeam = team1;
		player2.activeTeam = team2;

		//set chars stats(?)

		// add mobs to game

		//set start positions

		//add new GameMonitor to list

		
	}

	void GameMonitor::EndGame(Player player1, Player player2) //ends game and returns players to lobby (or boots inactive players)
	{
		//save stats to DB
		Players::SaveStats(player1.ID);
		Players::SaveStats(player2.ID);

		//kick players back to lobby

		//delete mobs

		//remove GameMonitor from list

	}

