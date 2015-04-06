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

	vec2 temp = TILEMAP->ConvertScreenToTileCoordinates(CAMERA->GetDrawablePosOnScreen(TILEMAP), vec2(x, y), CAMERA->GetScale());
	Player* currentPlayer = PLAYERS[ClientAPI::GetCurrentPlayer()];
	vector<Character*> chars = currentPlayer->GetCharacterList();

	for (int i = 0; i < chars.size(); i++)
	{
		vec2 charPosition = CAMERA->GetDrawablePosOnScreen(chars[i]);
		charPosition *= CAMERA->GetScale();
		vec2 temp = TILEMAP->ConvertScreenToTileCoordinates(CAMERA->GetDrawablePosOnScreen(TILEMAP), vec2(x, y), scale);

		//If mouse clicked on character OR mouse clicked on tile with a character
		//Set a character to be selected
		if (chars[i]->CollisionMouse(charPosition, x, y) ||
			(TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y, scale) && TILEMAP->GetTileAt(1, (int)temp.y, (int)temp.x)->GetCharacter() == chars[i]))
		{
			currentPlayer->SetCurrentActiveChar(chars[i]);
			TILEMAP->SetIsTileSelected(true, 1, (int)temp.y, (int)temp.x);

			if (currentPlayer->GetIsCharacterSelected())
				TILEMAP->SetIsTileSelected(false, prevSelectedTile.x, prevSelectedTile.y, prevSelectedTile.z);

			prevSelectedTile = vec3(1, temp.y, temp.x);
		}
		//If a character is selected, and the mouse is clicked on the map; move the character to the position clicked.
		else if (currentPlayer->GetIsCharacterSelected() && currentPlayer->GetCurrentActiveChar() == chars[i] && TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y, scale)
			&& TILEMAP->GetTileAt(1, (int)temp.y, (int)temp.x)->GetCharacter() == NULL)
		{
			if (!chars[i]->GetIsMoving())
			{
				chars[i]->Move(ClientAPI::tileMap, TILEMAP->GetTileAt(1, (int)temp.y, (int)temp.x));
				//currentPlayer->RemoveCurrentActiveChar();
				TILEMAP->SetIsTileSelected(false, prevSelectedTile.x, prevSelectedTile.y, prevSelectedTile.z);
				prevSelectedTile = vec3(1, temp.y, temp.x);
				TILEMAP->SetIsTileSelected(true, 1, (int)temp.y, (int)temp.x);
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
	{
		PLAYERS[ClientAPI::GetCurrentPlayer()]->EndTurn();
		TILEMAP->SetIsTileSelected(false, prevSelectedTile.x, prevSelectedTile.y, prevSelectedTile.z);
		ClientAPI::CycleToNextPlayer();
		PLAYERS[ClientAPI::GetCurrentPlayer()]->StartTurn();
	}

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
