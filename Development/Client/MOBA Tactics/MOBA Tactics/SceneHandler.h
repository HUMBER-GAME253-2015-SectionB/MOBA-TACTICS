//Author:	Nicholas Higa
//Date:		3/10/2015(NH),	4/12/2015(NH)

#pragma once

struct SDL_MouseWheelEvent;

#include "ClientAPI.h"
#include "glm\glm.hpp"

using namespace glm;

class SceneHandler
{
private:
	SceneHandler();
	vec2 prevSelectedTile;
	vec2 prevHoveredTile;
	Character *attackTarget;
public:
	static SceneHandler& GetInstance();
	void HandleEventMouseDown(int x, int y);
	void HandleEventMouseUp(int x, int y);
	void HandleEventMouseHover(int x, int y);
	void HandleEventKeyDown(unsigned key);
	void HandleEventKeyUp(unsigned key);
	void HandleEventMouseWheel(SDL_MouseWheelEvent mwheel);
};