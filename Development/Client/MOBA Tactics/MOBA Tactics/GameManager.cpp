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

			if( SDL_PollEvent(&evt) )
			{
				if(evt.type == SDL_QUIT || evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					newGame->Exit();
				}	
			}
			
			//Event Manager
			Game::eventManager.ManageEvents(&evt);

			lastUpdateTime = SDL_GetTicks();
			newGame->elaspedTime = timeSincelastUpdate;
			
			SDL_PumpEvents();
			
			//MAIN UPDATE CALL
			newGame->Update();

			//Post-update: set previous mouse state
			{
				newGame->eventManager.PreviousMouseState = newGame->eventManager.MouseState;
				newGame->eventManager.PreviousMouseX = newGame->eventManager.MouseX;
				newGame->eventManager.PreviousMouseY = newGame->eventManager.MouseY;
			}

			//MAIN DRAW CALL
			SDL_RenderClear(ClientAPI::mainRenderer);
			newGame->Draw();
			SDL_SetRenderDrawColor(ClientAPI::mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderPresent(ClientAPI::mainRenderer);
			
			/*
			SDL_RenderClear(newGame->Renderer);
			newGame->Draw();
			SDL_SetRenderDrawColor(newGame->Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderPresent(newGame->Renderer);
			*/

		}

	}

	newGame->UnloadContent();
}