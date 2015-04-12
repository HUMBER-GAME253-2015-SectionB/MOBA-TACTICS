/*
//James Finnie
Last Updated 04/11
*/

#pragma once
#include "Team.h"

class GameMonitor
{
public:
	GameMonitor(void);
	~GameMonitor(void);

	GameMonitor(int client1, int client2);

	bool CheckWinner(Team team1, Team team2);
	bool EndTurn(Team team);
	void StartTurn(Team team);

	void HealthCheck(Team team);
	void ActionCheck(Team team);
};

