//Author:	Mathieu Violette
//Date:		3/22/2014(MV)

#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_net.h>

#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <sstream>

class Game
{
	public:
		bool GameIsRunning;
		Uint32 elaspedTime;
		SDL_Window *Window;
		SDL_Renderer *Renderer;
		Game();
		~Game();
		void Init();
		void LoadContent();
		void UnloadContent();
		void Update();
		void Exit();	
};

#endif 