//Author:	Mathieu Violette
//Date:		3/4/2015(MV)

#ifndef GAMESTATE_MANAGER_H
#define GAMESTATE_MANAGER_H

#include "GameState.h"

class GameStateManager
{
	GameStateManager();
	GameState currentState;
public:
	static GameStateManager& GetInstance();
	~GameStateManager();
	GameState GetGameState();
	void ChangeToGameState(GameState _newGameState);
};

#endif