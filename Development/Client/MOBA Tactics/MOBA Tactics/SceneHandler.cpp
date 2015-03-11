//Author:	Nicholas Higa
//Date:		3/10/2015(NH)

#include "SceneHandler.h"

SceneHandler::SceneHandler()
{
}

void SceneHandler::HandleEventMouseDown(int x, int y)
{
	//game->GetCharacter()->
}

void SceneHandler::HandleEventMouseUp(int x, int y)
{

}

void SceneHandler::HandleEventMouseHover(int x, int y)
{

}

SceneHandler& SceneHandler::GetInstance()
{
	static SceneHandler instance;
	return instance;
}

void SceneHandler::SetGame(IGame *_game)
{
	game = _game;
}