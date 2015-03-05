//Author:	Mathieu Violette
//Date:		3/4/2015(MV)

#include "GameStateManager.h"

IGame* GameStateManager::gameObject;

GameStateManager& GameStateManager::GetInstance()
{
	static GameStateManager instance;
	return instance;
}

GameStateManager::GameStateManager()
{
	currentState = GameState::NONE;
	currentMenu = nullptr;
}

GameStateManager::~GameStateManager()
{
	if (currentMenu != nullptr)
		delete currentMenu;
}

GameState GameStateManager::GetGameState() const
{
	return currentState;
}

IMenu* GameStateManager::GetCurrentMenu() const
{
	return currentMenu;
}
	
void GameStateManager::SetGameObject(IGame* _game)
{
	if (gameObject == nullptr)
		gameObject = _game;
}

void GameStateManager::ChangeToGameState(GameState _newGameState)
{
	//Unload current state
	if (currentState == GameState::SCENE)
	{
		
	}
	else if (currentMenu != nullptr)
	{
		currentMenu->Unload();
		delete currentMenu;	
	}

	//Change current state to new state
	currentState = _newGameState;
	currentMenu = GetNewMenu(_newGameState);

	//Load new state
	if (_newGameState == GameState::SCENE)
	{
		
	}
	else if (currentMenu != nullptr)
	{
		currentMenu->Load();
	}	
}

IMenu* GameStateManager::GetNewMenu(GameState _newGameState)
{
	switch (_newGameState)
	{
		case GameState::NONE:
			return nullptr;
			break;
		case GameState::LOGIN:
			return new LoginScreen();
			break;
		case GameState::REGISTER:
			//return new LoginRegister();
			break;
		case GameState::MAINMENU:
			return new MainMenu();
			break;
		case GameState::OPTIONS:
			return new Options();
			break;
		case GameState::TEAM_VIEW:
			//return new TeamViewer();
			break;
		case GameState::TEAM_NEW:
			//return new TeamCreate();
			break;
		case GameState::TEAM_EDIT:
			//return new TeamEdit();
			break;
		case GameState::LOBBY_LIST:
			return new LobbyList();
			break;
		case GameState::LOBBY_ROOM:
			//return new LobbyRoom();
			break;
	}

	return nullptr;
}