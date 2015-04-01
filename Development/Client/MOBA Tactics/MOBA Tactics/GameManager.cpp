//Author:	Mathieu Violette
//Date:		3/22/2014(MV), 3/4/2015(MV)

#include "GameManager.h"

Game* GameManager::newGame = nullptr;
GameStateManager Game::gameStateManager = GameStateManager::GetInstance();
EventManager Game::eventManager = EventManager::GetInstance();

GameManager::GameManager()
{
	lastUpdateTime = 0, timeSincelastUpdate = 0;

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

			while( SDL_PollEvent(&evt) )
			{
				if(evt.type == SDL_QUIT || evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					newGame->Exit();
				}	
				//Event Manager
				Game::eventManager.ManageEvents(&evt);
			}			

			lastUpdateTime = SDL_GetTicks();
			newGame->elaspedTime = timeSincelastUpdate;
			ClientAPI::elaspedTime = timeSincelastUpdate;
			
			SDL_PumpEvents();
			
			//MAIN UPDATE CALL
			newGame->gameStateManager.UpdateGameState();
			newGame->Update();

			//MAIN DRAW CALL
			SDL_RenderClear(ClientAPI::mainRenderer);
			newGame->Draw();

			if (Game::eventManager.test)
				SDL_SetRenderDrawColor(ClientAPI::mainRenderer, 0xFF, 0x00, 0x00, 0xFF);
			else
				SDL_SetRenderDrawColor(ClientAPI::mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			
			SDL_RenderPresent(ClientAPI::mainRenderer);

		}

	}

	newGame->UnloadContent();
}