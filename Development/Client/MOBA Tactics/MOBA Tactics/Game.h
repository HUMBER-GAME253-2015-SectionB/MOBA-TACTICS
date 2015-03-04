//Author:	Mathieu Violette
//Date:		3/22/2014(MV)

#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "ClientAPI.h"
#include "TileMap.h"
#include "Character.h"

class Game
{
	public:
		bool GameIsRunning;
		Uint32 elaspedTime;
		SDL_Window *Window;
		SDL_Renderer *Renderer;
		SDL_Event *oldMouseState;
		Game();
		~Game();
		void Init();
		void LoadContent();
		void UnloadContent();
		void OnEvent(SDL_Event *event);
		void UpdateInput(SDL_Event *event);
		void Update();
		void Draw();
		void Exit();	
};

#endif 