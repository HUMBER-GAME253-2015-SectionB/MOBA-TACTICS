/*
//James Finnie
Last Updated 04/21
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
		EndRound(player1, player2);

		//here we go again!
		StartTurn(player1); // this will have to go if we get mobs in, move if not
	}
	
}

bool GameMonitor::CheckWinner(Player player1, Player player2)
{
	if (player1.score >= 1000)
	{
		//declare team1 the winner
		//SendString(player1.id, "g/w/win/");
		//SendString(player2.id, "g/w/lose/");

		return true;
	}
	else if (player2.score >= 1000)
	{
		//declare team2 the winner
		//SendString(player2.id, "g/w/win/");
		//SendString(player1.id, "g/w/lose/");

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

	//if the game still thinks its their tuen but no characters can act
	if (!player.wait && !team._Characters[0].active && !team._Characters[1].active && !team._Characters[2].active)
	{
		//end turn
		player.wait = true;
		//notfiy player
		//SendString(player.id, "g/t/false/");
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
			team._Characters[i].curDef = team._Characters[i].maxDef;
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
				team._Characters[i].curDef = team._Characters[i].maxDef;
				team._Characters[i].curAP = team._Characters[i].maxAP;
				//reset states
				team._Characters[i].alive = true;
				team._Characters[i].active = true;

				//reset pos 
				team._Characters[i].posX = team._Characters[i].startX;
				team._Characters[i].posY = team._Characters[i].startY;

				//update players
				//SendString(player.id, player.opponent, "g/c/" + std::to_string(i) + "/reset/");
			}

		}
	}
	//Go!
	player.wait = false;
	//notify player
	//SendString(player.id, "g/t/true");
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
			//SendString(player.id, player.opponent, "g/c/" + std::to_string(i) + "/dead/");

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

	void GameMonitor::StartGame(Player player1, int team1, Player player2, int team2) //may send just an int and we grab from storedTeams arr
	{
		//assign active team
		player1.activeTeam = player1.storedTeams[team1];
		player2.activeTeam = player2.storedTeams[team2];

		player1.opponent = player2.ID;
		player2.opponent = player1.ID;

		//set chars stats from DB(?)

		// add mobs to game
		//set start positions P1
		Team P1 = player1.activeTeam;

		P1._Characters[0].startX = 3; P1._Characters[0].startY = 3;
		P1._Characters[0].startX = 3; P1._Characters[0].startY = 2;
		P1._Characters[0].startX = 2; P1._Characters[0].startY = 3;

		//set start positions P2
		Team P2 = player2.activeTeam;

		P2._Characters[0].startX = 17; P2._Characters[0].startY = 17;
		P2._Characters[0].startX = 18; P2._Characters[0].startY = 17;
		P2._Characters[0].startX = 17; P2._Characters[0].startY = 18;

		//add new GameMonitor to list
		GameMonitor newGame = GameMonitor(player1, player2);
		newGame.ref = player1.ID;
		activeGames.push_back(newGame);
	}

	void GameMonitor::EndGame(Player player1, Player player2) //ends game and returns players to lobby (or boots inactive players)
	{
		//save stats to DB
		Players::SaveStats(player1.ID);
		Players::SaveStats(player2.ID);

		//kick players back to lobby
		//done via string message?
		//SendString(player1.id, player2.id, "g/gameOver/");

		//delete mobs
		//remove GameMonitor from list
		for(int i = 0; i < activeGames.size() - 1; i++)
		{
			if(activeGames[i].ref == (player1.ID || player2.ID))
			{
				activeGames.erase(activeGames.begin() + i);
				break;
			}
		}

	}

	void GameMonitor::EndRound(Player player1, Player player2)
	{
		for(int i = 0; i < 3; i++)
		{
			
			//check player 1 positions and update score as needed
			if(player1.activeTeam._Characters[i].alive && //has to be alive to count
				(player1.activeTeam._Characters[i].posX == (9 || 10 || 11) && 
				player1.activeTeam._Characters[i].posY == (9 || 10 || 11))) //i may have gone a little crazy here, be careful with this!
			{
				player1.score += 100;
			}

			//same for player 2
			if(player2.activeTeam._Characters[i].alive && //has to be alive to count
				(player2.activeTeam._Characters[i].posX == (9 || 10 || 11) && 
				player2.activeTeam._Characters[i].posY == (9 || 10 || 11))) //i may (still) have gone a little crazy here, be careful with this!
			{
				player2.score += 100;
			}
		}

		//send players updated scores 
		//SendString(player1.id, "g/score/ + std::to_string(player1.score) + "/enemyScore/ + std::to_string(player2.score) + "/");
		//SendString(player2.id, "g/score/ + std::to_string(player2.score) + "/enemyScore/ + std::to_string(player1.score) + "/");
	}

