//Author:	Mathieu Violette
//Date:		3/22/2014(MV)

#ifndef __GAMEMANAGER_H_INCLUDED__
#define __GAMEMANAGER_H_INCLUDED__
#include "Game.h"

class GameManager
{
	private:
		static Game *newGame;
	public:
		GameManager();
		~GameManager();
		void StartProgram();
		static int SDL_UpdateThreadFunction(void*);
		static int SDL_DrawThreadFunction(void*);
};

#endif 