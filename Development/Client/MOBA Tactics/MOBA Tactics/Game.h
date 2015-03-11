//Author:	Mathieu Violette
//Date:		3/22/2014(MV), 3/4/2015(MV)

#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

class GameStateManager;
class EventManager;
class Character;
class TileMap;

#include "IGame.h"
#include "ClientAPI.h"
#include "TileMap.h"
#include "Character.h"
#include "GameStateManager.h"
#include "EventManager.h"

class Game : public IGame
{
	public:
		bool GameIsRunning;
		Uint32 elaspedTime;
		//SDL_Window *Window;
		int renWidth, renHeight;
		//SDL_Renderer *Renderer;
		static GameStateManager gameStateManager;
		static EventManager eventManager;

		TileMap *tiles;
		Character *character;
		
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

		Character* GetCharacter();
		TileMap* GetTileMap();
};

#endif 