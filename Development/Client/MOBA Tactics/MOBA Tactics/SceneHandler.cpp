//Author:	Nicholas Higa, MAthieu Violette
//Date:		3/10/2015(NH), 3/11/2015(NH), 3/15/2015 (NH), 3/18/2015(MV)

#include "SceneHandler.h"
#include "TileMap.h"
#include "Character.h"
#include "Camera.h"

SceneHandler::SceneHandler()
{
	prevHighlightedTile = vec3(0, 0, 0);
}

void SceneHandler::HandleEventMouseDown(int x, int y)
{
	if (TILEMAP->IsPointOnMap(CAMERA->GetDrawablePosOnScreen(TILEMAP), x, y) && CHARACTER->GetIsSelected())
	{
		vec2 temp = TILEMAP->ConvertScreenToTileCoordinates(CAMERA->GetDrawablePosOnScreen(TILEMAP), vec2(x, y));
		printf("Clicked on (%f, %f)\n", temp.x, temp.y);
		CHARACTER->Move(ClientAPI::tileMap, TILEMAP->GetTileAt(1, (int)temp.y, (int)temp.x));
		CHARACTER->SetIsSelected(false);
	}

	vec2 charPosition = CAMERA->GetDrawablePosOnScreen(CHARACTER);
	charPosition *= CAMERA->GetScale();

	if (!CHARACTER->GetIsSelected() && CHARACTER->CollisionMouse(charPosition, x, y))
	{
		printf("Character selected\n");
		CHARACTER->SetIsSelected(true);
		CAMERA->CentreOn(vec2(x, y));
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
}

void SceneHandler::HandleEventKeyUp(unsigned key)
{

}

void SceneHandler::HandleEventMouseWheel(SDL_MouseWheelEvent mwheel)
{
	if (mwheel.y > 0)
		CAMERA->SetScale(CAMERA->GetScale() + 0.3f);
	else if (mwheel.y < 0)
		CAMERA->SetScale(CAMERA->GetScale() - 0.3f);
}

SceneHandler& SceneHandler::GetInstance()
{
	static SceneHandler instance;
	return instance;
}
