//Author:	Nicholas Higa
//Date:		3/10/2015(NH)

#pragma once

#include "IGame.h"

class SceneHandler
{
private:
	SceneHandler();
	IGame *game;
public:
	static SceneHandler& GetInstance();
	void HandleEventMouseDown(int x, int y);
	void HandleEventMouseUp(int x, int y);
	void HandleEventMouseHover(int x, int y);

	void SetGame(IGame *_game);
};