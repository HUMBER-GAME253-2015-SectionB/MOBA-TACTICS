//Author:	Nicholas Higa
//Date:		3/10/2015(NH), 3/11/2015(NH), 3/15/2015 (NH)

#include "SceneHandler.h"

SceneHandler::SceneHandler()
{
	prevHighlightedTile = vec3(0, 0, 0);
}

void SceneHandler::HandleEventMouseDown(int x, int y)
{
	if (game->GetTileMap()->IsPointOnMap(game->camera->GetDrawablePosOnScreen(game->tiles), x, y))
	{
		vec2 temp = game->GetTileMap()->ConvertScreenToTileCoordinates(game->camera->GetDrawablePosOnScreen(game->tiles), vec2(x, y));
		printf("Clicked on (%f, %f)\n", temp.x, temp.y);
		game->GetCharacter()->Move(game->GetTileMap(), game->GetTileMap()->GetTileAt(1, (int)temp.y, (int)temp.x));
	}
}

void SceneHandler::HandleEventMouseUp(int x, int y)
{

}

void SceneHandler::HandleEventMouseHover(int x, int y)
{
	if (game->GetTileMap()->IsPointOnMap(game->camera->GetDrawablePosOnScreen(game->tiles), x, y))
	{
		vec2 temp = game->GetTileMap()->ConvertScreenToTileCoordinates(game->camera->GetDrawablePosOnScreen(game->tiles), vec2(x, y));

		if (prevHighlightedTile != vec3(1, temp.y, temp.x))
		{
			game->GetTileMap()->SetIsTileHighlighted(true, 1, (int)temp.y, (int)temp.x);
			game->GetTileMap()->SetIsTileHighlighted(false, (int)prevHighlightedTile.x, (int)prevHighlightedTile.y, (int)prevHighlightedTile.z);
		}
		prevHighlightedTile = vec3(1, temp.y, temp.x);
	}
	else
	{
		game->GetTileMap()->SetIsTileHighlighted(false, (int)prevHighlightedTile.x, (int)prevHighlightedTile.y, (int)prevHighlightedTile.z);
	}
}

void SceneHandler::HandleEventKeyDown(SDL_Event *event)
{
	switch (event->key.keysym.sym)
	{
		case SDLK_UP:
			game->camera->MoveCamera(vec2(0, 5));
			break;
		case SDLK_DOWN:
			game->camera->MoveCamera(vec2(0, -5));
			break;
		case SDLK_LEFT:
			game->camera->MoveCamera(vec2(5, 0));
			break;
		case SDLK_RIGHT:
			game->camera->MoveCamera(vec2(-5, 0));
			break;
		default:
			break;
	}
}

void SceneHandler::HandleEventKeyUp(SDL_Event *event)
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