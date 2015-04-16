/*
//James Finnie
Last Updated 04/11
*/

#pragma once
#include "Team.h"
#include "Players.h"

class GameMonitor
{
public:
	GameMonitor(void);
	~GameMonitor(void);

	GameMonitor(Player player1, Player player2);

	bool CheckWinner(Player player1, Player player2);
	bool EndTurn(Player player);
	void StartTurn(Player player);

	void HealthCheck(Team team);
	void ActionCheck(Team team);

	void StartGame(Player player1, Team team1, Player player2, Team team2); //may send just an int and we grab from storedTeams arr
	void EndGame(Player player1, Player player2); //ends game and returns players to lobby (or boots inactive players)

private:
	
};

