//Author:	Mathieu Violette
//Date:		3/22/2014(MV), 3/4/2015(MV)

#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "IGame.h"
#include "ClientAPI.h"
#include "TileMap.h"
#include "Character.h"
#include "GameStateManager.h"

class Game : public IGame
{
	public:
		bool GameIsRunning;
		Uint32 elaspedTime;
		SDL_Window *Window;
		int renWidth, renHeight;
		SDL_Renderer *Renderer;
		static GameStateManager gameStateManager;

		const Uint8 *KeyState;
		int MouseX, MouseY;
		Uint32 MouseState;
		int PreviousMouseX, PreviousMouseY;
		Uint32 PreviousMouseState;

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