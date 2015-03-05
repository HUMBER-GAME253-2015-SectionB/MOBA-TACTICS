//Author:	Mathieu Violette
//Date:		3/22/2014(MV), 3/4/2015(MV)

#include "GameManager.h"

Game* GameManager::newGame = nullptr;
GameStateManager Game::gameStateManager = GameStateManager::GetInstance();

GameManager::GameManager()
{
	lastUpdateTime = 0, timeSincelastUpdate = 0;

	newGame = new Game();
	Game::gameStateManager.SetGameObject(newGame);
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
				//Event Manager
				
			}
		
			lastUpdateTime = SDL_GetTicks();
			newGame->elaspedTime = timeSincelastUpdate;
			
			SDL_PumpEvents();

			//Pre-update: Get mouse state
			newGame->MouseState = SDL_GetMouseState(&newGame->MouseX, &newGame->MouseY); 
			
			//MAIN UPDATE CALL
			newGame->Update();

			//Post-update: set previous mouse state
			{
				newGame->PreviousMouseState = newGame->MouseState;
				newGame->PreviousMouseX = newGame->MouseX;
				newGame->PreviousMouseY = newGame->MouseY;
			}

			//MAIN DRAW CALL
			SDL_RenderClear(newGame->Renderer);
			newGame->Draw();
			SDL_SetRenderDrawColor(newGame->Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderPresent(newGame->Renderer);
		}

	}

	newGame->UnloadContent();
}