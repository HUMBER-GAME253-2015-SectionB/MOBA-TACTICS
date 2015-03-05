//Author:	Mathieu Violette
//Date:		3/4/2015(MV)

#include "GameStateManager.h"

GameStateManager& GameStateManager::GetInstance()
{
	static GameStateManager instance;
	return instance;
}

GameStateManager::GameStateManager()
{
	currentState = GameState::NONE;
}

GameStateManager::~GameStateManager(){}

GameState GameStateManager::GetGameState()
{
	return currentState;
}
	
void GameStateManager::ChangeToGameState(GameState _newGameState)
{
	//Unload current state
	switch (currentState)
	{
		case GameState::NONE:
			break;
		case GameState::LOGIN:
			break;
		case GameState::REGISTER:
			break;
		case GameState::MAINMENU:
			break;
		case GameState::OPTIONS:
			break;
		case GameState::TEAM_VIEW:
			break;
		case GameState::TEAM_NEW:
			break;
		case GameState::TEAM_EDIT:
			break;
		case GameState::LOBBY_LIST:
			break;
		case GameState::LOBBY_ROOM:
			break;
		case GameState::SCENE:
			break;
	}

	//Load new state
	switch (_newGameState)
	{
		case GameState::NONE:
			break;
		case GameState::LOGIN:
			break;
		case GameState::REGISTER:
			break;
		case GameState::MAINMENU:
			break;
		case GameState::OPTIONS:
			break;
		case GameState::TEAM_VIEW:
			break;
		case GameState::TEAM_NEW:
			break;
		case GameState::TEAM_EDIT:
			break;
		case GameState::LOBBY_LIST:
			break;
		case GameState::LOBBY_ROOM:
			break;
		case GameState::SCENE:
			break;
	}
	
	//Change current state to new state
	currentState = _newGameState;
}
