//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#ifndef IMENU_H
#define IMENU_H

#include <SDL.h>

class IMenu
{
public:
	virtual ~IMenu() = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	virtual void Draw(SDL_Renderer*) const = 0;
};

inline IMenu::~IMenu(){}

#endif