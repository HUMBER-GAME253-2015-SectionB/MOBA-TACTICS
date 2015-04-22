#pragma once
#include "Team.h"
#include "Players.h"
#include "NPC.h"
/*
//James Finnie
Last Updated 04/21
*/
class GameMonitor
{
public:

	Player players[2];
	std::vector <NPC> npc;


	GameMonitor(void);
	~GameMonitor(void);

	GameMonitor(Player player1, Player player2);
	
	bool CheckWinner(Player player1, Player player2);
	bool EndTurn(Player player);
	void StartTurn(Player player);
	void EndRound(Player player1, Player player2);

	void HealthCheck(Team team);
	void ActionCheck(Team team);

	void StartGame(Player player1, int team1, Player player2, int team2); // creates game with selected teams
	void EndGame(Player player1, Player player2); //ends game and returns players to lobby (or boots inactive players)

private:
	static std::vector<GameMonitor> activeGames;
	static int ref;
};

