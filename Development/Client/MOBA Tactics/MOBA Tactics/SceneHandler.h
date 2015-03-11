//Author:	Nicholas Higa
//Date:		3/10/2015(NH)

#pragma once

class Game;

#include "Game.h"

class SceneHandler
{
private:
	SceneHandler();
	Game *game;
public:
	static SceneHandler& GetInstance();
	void HandleEventMouseDown(int x, int y);
	void HandleEventMouseUp(int x, int y);
	void HandleEventMouseHover(int x, int y);

	void SetGame(Game *_game);
};