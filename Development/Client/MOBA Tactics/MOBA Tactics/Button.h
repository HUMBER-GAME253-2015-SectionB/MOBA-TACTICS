//Author:	Alejandro Zielinsky
//Date:		3/4/2015(AZ)
#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>
enum ButtonState{UNPRESSED, PRESSED, HOVER};
class Button
{
private:
	SDL_Rect box; 

public:
	Button();
	void onClick();
	void show();
	ButtonState btnState;

};

