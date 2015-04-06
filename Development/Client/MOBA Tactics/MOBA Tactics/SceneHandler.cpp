//Author:	Nicholas Higa, MAthieu Violette
//Date:		3/10/2015(NH), 3/11/2015(NH), 3/15/2015 (NH), 3/18/2015(MV),
//			3/30/2015(NH), 4/6/2015(NH)

#include "SceneHandler.h"
#include "TileMap.h"
#include "Character.h"
#include "Camera.h"
#include "Player.h"

SceneHandler::SceneHandler()
{
	prevHighlightedTile = vec3(0, 0, 0);
}

void SceneHandler::HandleEventMouseDown(int x, int y)
{
	float scale = CAMERA->GetScale();

	vector<Character*> chars = PLAYERS[ClientAPI::GetCurrentPlayer()]->GetCharacterList();
	vec2 temp = TILEMAP->ConvertScreenToTileCoordinates(CAMERA->GetDrawablePosOnScreen(TILEMAP), vec2(x, y), CAMERA->GetScale());

	for (int i = 0; i < chars.size(); i++)
	{
		//If character is already selected, and a tile is clicked; move to the clicked tile
		if (TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y, scale) && chars[i]->GetIsSelected())
		{
			vec2 temp = TILEMAP->ConvertScreenToTileCoordinates(CAMERA->GetDrawablePosOnScreen(TILEMAP), vec2(x, y), scale);
			//printf("Clicked on (%f, %f)\n", temp.x, temp.y);
			chars[i]->Move(ClientAPI::tileMap, TILEMAP->GetTileAt(1, (int)temp.y, (int)temp.x));
			chars[i]->SetIsSelected(false);
			TILEMAP->SetIsTileSelected(false, prevSelectedTile.x, prevSelectedTile.y, prevSelectedTile.z);
		}

		vec2 charPosition = CAMERA->GetDrawablePosOnScreen(chars[i]);
		charPosition *= CAMERA->GetScale(); 

		//If player clicks on a character and the character is not selected already, select the character
		if (!chars[i]->GetIsSelected() && chars[i]->CollisionMouse(charPosition, x, y))
		{
			printf("Character selected by character click\n");
			chars[i]->SetIsSelected(true);
			CAMERA->CentreOn(vec2(x, y));
			TILEMAP->SetIsTileSelected(true, 1, (int)temp.y, (int)temp.x);
			prevSelectedTile = vec3(1, temp.y, temp.x);
		}
		else if (!chars[i]->GetIsSelected() && TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y, scale))
		{
			vec2 temp = TILEMAP->ConvertScreenToTileCoordinates(CAMERA->GetDrawablePosOnScreen(TILEMAP), vec2(x, y), scale);
			
			//This statement allows the player to click on a tile with a character on it to select the character.
			if (TILEMAP->GetTileAt(1, (int)temp.y, (int)temp.x)->GetIsOccupied())
			{
				if (TILEMAP->GetTileAt(1, (int)temp.y, (int)temp.x)->GetCharacter() == chars[i])
				{
					printf("Character selected by tile click\n");
					chars[i]->SetIsSelected(true);
					CAMERA->CentreOn(vec2(x, y));
					TILEMAP->SetIsTileSelected(true, 1, (int)temp.y, (int)temp.x);
					prevSelectedTile = vec3(1, temp.y, temp.x);
				}
			}
		}
	}
}

void SceneHandler::HandleEventMouseUp(int x, int y)
{

}

void SceneHandler::HandleEventMouseHover(int x, int y)
{
	if (TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y, CAMERA->GetScale()))
	{
		vec2 temp = TILEMAP->ConvertScreenToTileCoordinates(CAMERA->GetDrawablePosOnScreen(TILEMAP), vec2(x, y), CAMERA->GetScale());

		if (prevHighlightedTile != vec3(1, temp.y, temp.x))
		{
			TILEMAP->SetIsTileHighlighted(true, 1, (int)temp.y, (int)temp.x);
			TILEMAP->SetIsTileHighlighted(false, (int)prevHighlightedTile.x, (int)prevHighlightedTile.y, (int)prevHighlightedTile.z);
		}

		prevHighlightedTile = vec3(1, temp.y, temp.x);
	}
	else
	{
		TILEMAP->SetIsTileHighlighted(false, (int)prevHighlightedTile.x, (int)prevHighlightedTile.y, (int)prevHighlightedTile.z);
	}
}

void SceneHandler::HandleEventKeyDown(unsigned key)
{
	if (key == SDLK_UP)
		CAMERA->MoveCamera(vec2(0, 22));

	if (key == SDLK_DOWN)
		CAMERA->MoveCamera(vec2(0, -22));

	if (key == SDLK_LEFT)
		CAMERA->MoveCamera(vec2(22, 0));

	if (key == SDLK_RIGHT)
		CAMERA->MoveCamera(vec2(-22, 0));

	if (key == SDLK_e)
		ClientAPI::CycleToNextPlayer();
}

void SceneHandler::HandleEventKeyUp(unsigned key)
{

}

void SceneHandler::HandleEventMouseWheel(SDL_MouseWheelEvent mwheel)
{
	if (mwheel.y > 0)
		CAMERA->SetScale(CAMERA->GetScale() + 0.3);
	else if (mwheel.y < 0)
		CAMERA->SetScale(CAMERA->GetScale() - 0.3);
}

SceneHandler& SceneHandler::GetInstance()
{
	static SceneHandler instance;
	return instance;
}
