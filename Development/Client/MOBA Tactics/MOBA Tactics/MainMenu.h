//Author:	David Vo, Mathieu Violette
//Date:		2/23/2014(DV), 3/5/2015(MV)

#ifndef __MAINMENU_H_INCLUDED__
#define __MAINMENU_H_INCLUDED__

#include "IMenu.h"

class MainMenu : public IMenu
{
public:
	MainMenu();
	~MainMenu();

	void Load();
	void Unload();
	void Update();
	void Draw(SDL_Renderer* ren);

private:

};

#endif