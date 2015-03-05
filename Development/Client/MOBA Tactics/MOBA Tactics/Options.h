//Author:	David Vo, Mathieu Violette
//Date:		2/23/2014(DV), 3/5/2015(MV)

#ifndef __OPTIONS_H_INCLUDED__
#define __OPTIONS_H_INCLUDED__

#include "IMenu.h"

class Options : public IMenu
{
public:
	Options();
	~Options();

	void Load();
	void Unload();
	void Update();
	void Draw(SDL_Renderer* ren);

private:

};
#endif