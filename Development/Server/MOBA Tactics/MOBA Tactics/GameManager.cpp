//Author:	Mathieu Violette
//Date:		3/22/2014(MV)

#include "GameManager.h"

Game* GameManager::newGame = nullptr;
Uint32 lastUpdateTime = 0, timeSincelastUpdate = 0;

GameManager::GameManager()
{
	newGame = new Game();
}

GameManager::~GameManager()
{
	delete newGame;
}

void GameManager::StartProgram()
{
	newGame->Init();
	newGame->LoadContent();

	SDL_Event evt;

	//Game Loop
	while(newGame->GameIsRunning)
	{
		timeSincelastUpdate = SDL_GetTicks() - lastUpdateTime;
		if (timeSincelastUpdate >= 16)
		{

			if( SDL_PollEvent(&evt) )
			{
				if(evt.type == SDL_QUIT || evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					newGame->Exit();
				}
			}
		
			lastUpdateTime = SDL_GetTicks();
			newGame->elaspedTime = timeSincelastUpdate;
			
			SDL_PumpEvents();
			newGame->Update();
			newGame->Draw();

		}

	}

	newGame->UnloadContent();
}