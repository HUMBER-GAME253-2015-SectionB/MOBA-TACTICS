//Author:	Mathieu Violette
//Date:		3/22/2014(MV)

#ifndef __GAMEMANAGER_H_INCLUDED__
#define __GAMEMANAGER_H_INCLUDED__

#include "Game.h"

class GameManager
{
	private:
		static Game *newGame;
		Uint32 lastUpdateTime, timeSincelastUpdate;
	public:
		GameManager();
		~GameManager();
		void StartProgram();
};

#endif 