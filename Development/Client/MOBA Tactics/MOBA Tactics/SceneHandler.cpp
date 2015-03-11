//Author:	Nicholas Higa
//Date:		3/10/2015(NH), 3/11/2015(NH)

#include "SceneHandler.h"

SceneHandler::SceneHandler()
{
}

void SceneHandler::HandleEventMouseDown(int x, int y)
{
	//TODO: Figure out why certain tile clicks don't get detected.
	if (game->GetTileMap()->CollisionMouse(x, y))
	{
		vec2 temp = game->GetTileMap()->ConvertScreenToTileCoordinates(vec2(x, y));
		printf("Clicked on (%f, %f)\n", temp.x, temp.y);
		game->GetCharacter()->Move(game->GetTileMap(), game->GetTileMap()->GetTileAt(1, temp.y, temp.x));
	}
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

void SceneHandler::SetGame(Game *_game)
{
	game = _game;
}