//Author:	Nicholas Higa
//Date:		3/10/2015(NH)

#pragma once

struct SDL_MouseWheelEvent;

#include "ClientAPI.h"
#include "glm\glm.hpp"

using namespace glm;

class SceneHandler
{
private:
	SceneHandler();
	vec2 prevHighlightedTile;
	vec2 prevSelectedTile;
public:
	static SceneHandler& GetInstance();
	void HandleEventMouseDown(int x, int y);
	void HandleEventMouseUp(int x, int y);
	void HandleEventMouseHover(int x, int y);
	void HandleEventKeyDown(unsigned key);
	void HandleEventKeyUp(unsigned key);
	void HandleEventMouseWheel(SDL_MouseWheelEvent mwheel);
};