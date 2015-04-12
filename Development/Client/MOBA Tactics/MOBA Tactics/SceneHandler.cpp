//Author:	Nicholas Higa, MAthieu Violette
//Date:		3/10/2015(NH), 3/11/2015(NH), 3/15/2015(NH), 3/18/2015(MV),
//			3/30/2015(NH), 4/6/2015(NH), 4/8/2015(NH), 4/9/2015(NH), 
//			4/11/2015(NH)

#include "SceneHandler.h"
#include "TileMap.h"
#include "Character.h"
#include "Camera.h"
#include "Player.h"

SceneHandler::SceneHandler()
{
	prevSelectedTile = vec2(0, 0);
	prevHoveredTile = vec2(0, 0);
}

void SceneHandler::HandleEventMouseDown(int x, int y)
{
	float scale = CAMERA->GetScale();

	vec2 temp = TILEMAP->ConvertScreenToTileCoordinates(CAMERA->GetDrawablePosOnScreen(TILEMAP), vec2(x, y), CAMERA->GetScale());
	Player* currentPlayer = PLAYERS[ClientAPI::GetCurrentPlayer()];
	vector<Character*> chars = currentPlayer->GetCharacterList();

	//Priint out which tiles are occupied
	/*printf("\n");
	for (int i = 0; i < TILEMAP->GetNumHeight(); i++)
	{
		for (int j = 0; j < TILEMAP->GetNumWidth(); j++)
		{
			if (TILEMAP->GetTileAt(i, j)->GetCharacter() == NULL)
				printf("x "); //Not occupied
			else
				printf("o "); //Occupied
		}
		printf("\n");
	}*/

	for (int i = 0; i < chars.size(); i++)
	{
		vec2 charPosition = CAMERA->GetDrawablePosOnScreen(chars[i]);
		charPosition *= CAMERA->GetScale();

		//If mouse clicked on character OR mouse clicked on tile with a character
		//Set a character to be selected
		if (chars[i]->CollisionMouse(charPosition, x, y) ||
			(TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y, scale) && TILEMAP->GetTileAt((int)temp.y, (int)temp.x)->GetCharacter() == chars[i]))
		{
			currentPlayer->SetCurrentActiveChar(chars[i]);
			TILEMAP->SetIsTileSelected(true, (int)temp.y, (int)temp.x);

			if (currentPlayer->GetIsCharacterSelected())
				TILEMAP->SetIsTileSelected(false, prevSelectedTile.x, prevSelectedTile.y);

			prevSelectedTile = vec2(temp.y, temp.x);
		}
		//If a character is selected
		else if (currentPlayer->GetIsCharacterSelected() && currentPlayer->GetCurrentActiveChar() == chars[i])
		{
			//If the mouse is clicked on the map; move the character to the position clicked.
			if (TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y, scale)
				&& TILEMAP->GetTileAt((int)temp.y, (int)temp.x)->GetCharacter() == NULL)
			{
				if (chars[i]->GetCharacterState() == CharacterState::MOVEMENT_SELECTED)
				{
					chars[i]->Move((int)temp.y, (int)temp.x);
					//currentPlayer->RemoveCurrentActiveChar();
					TILEMAP->SetIsTileSelected(false, prevSelectedTile.x, prevSelectedTile.y);
					prevSelectedTile = vec2(temp.y, temp.x);
					TILEMAP->SetIsTileSelected(true, (int)temp.y, (int)temp.x);
				}
			}
			else if (TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y, scale)
				&& TILEMAP->GetTileAt((int)temp.y, (int)temp.x)->GetCharacter() != NULL)
			{
				Character *targetChar = TILEMAP->GetTileAt((int)temp.y, (int)temp.x)->GetCharacter();
				if (chars[i]->GetCharacterState() == CharacterState::ATTACK_SELECTED)
				{
					chars[i]->Attack(TILEMAP->GetTileAt((int)temp.y, (int)temp.x)->GetCharacter());
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
	Player* currentPlayer = PLAYERS[ClientAPI::GetCurrentPlayer()];
	Character* currentCharacter = currentPlayer->GetCurrentActiveChar();
	CharacterState currentState = currentCharacter->GetCharacterState();

	if (TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y, CAMERA->GetScale()))
	{
		vec2 temp = TILEMAP->ConvertScreenToTileCoordinates(CAMERA->GetDrawablePosOnScreen(TILEMAP), vec2(x, y), CAMERA->GetScale());

		if (prevHoveredTile != vec2(temp.y, temp.x))
		{
			TILEMAP->SetIsTileHovered(true, 1, (int)temp.y, (int)temp.x);
			TILEMAP->SetIsTileHovered(false, (int)prevHoveredTile.x, (int)prevHoveredTile.y);
		}

		prevHoveredTile = vec2(temp.y, temp.x);
	}
	else
	{
		TILEMAP->SetIsTileHovered(false, (int)prevHoveredTile.x, (int)prevHoveredTile.y);
	}
}

void SceneHandler::HandleEventKeyDown(unsigned key)
{
	Player* currentPlayer = PLAYERS[ClientAPI::GetCurrentPlayer()];
	Character* currentCharacter = currentPlayer->GetCurrentActiveChar();
	CharacterState currentState = currentCharacter->GetCharacterState();

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
		currentPlayer->EndTurn();
		TILEMAP->SetIsTileSelected(false, prevSelectedTile.x, prevSelectedTile.y);
		ClientAPI::CycleToNextPlayer();
		currentPlayer->StartTurn();
	}

	if (key == SDLK_m)
	{
		if (currentState == CharacterState::SELECTED || currentState == CharacterState::ATTACK_SELECTED)
			currentCharacter->SetCharacterState(CharacterState::MOVEMENT_SELECTED);
	}

	if (key == SDLK_a)
	{
		if (currentState == CharacterState::SELECTED || currentState == CharacterState::MOVEMENT_SELECTED)
			currentCharacter->SetCharacterState(CharacterState::ATTACK_SELECTED);
	}

	if (key == SDLK_BACKSPACE)
	{
		if (currentState == CharacterState::ATTACK_SELECTED
			|| currentState == CharacterState::MOVEMENT_SELECTED)
			currentCharacter->SetCharacterState(CharacterState::SELECTED);
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
