//Author:	Mathieu Violette, Nicholas Higa
//Date:		3/22/2014(MV), 3/4/2015(MV), 3/30/2015(NH)

#include "Game.h"

//FOR DEBUGGING: SWITCH TO DIFFERENT STARTING STATE
GameState startingState = GameState::SPLASH;
//GameState startingState = GameState::SCENE;


Game::Game()
{
	GameIsRunning = true;
	elaspedTime = 0;

	eventManager.KeyState = SDL_GetKeyboardState(NULL);
	scene = new Scene();
}

Game::~Game(){}

void Game::Init()
{
	ClientAPI::mainWindow = nullptr;
	ClientAPI::mainWindow = SDL_CreateWindow("MOBA-Tactics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

	ClientAPI::mainRenderer = nullptr;
	ClientAPI::mainRenderer = SDL_CreateRenderer(ClientAPI::mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor	(ClientAPI::mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 400);
	SDL_GetRendererOutputSize(ClientAPI::mainRenderer, &renWidth, &renHeight);

	ClientAPI::mainRenderer = ClientAPI::mainRenderer;
	ClientAPI::mainWindow = ClientAPI::mainWindow;

	ClientAPI::Font.Init_Fonts();

	//Initialize random
	srand(time(NULL));	

	scene->Init();
}

void Game::LoadContent()
{
	scene->LoadContent();
}

void Game::UnloadContent()
{
	//End program
	scene->UnloadContent();
	
	Mix_FreeChunk(ClientAPI::_audioChannel);
	Mix_FreeChunk(ClientAPI::_audioChannel1);
	Mix_FreeChunk(ClientAPI::_audioChannel2);
	Mix_FreeChunk(ClientAPI::_audioChannel3);

	ClientAPI::_audioChannel = NULL;
	ClientAPI::_audioChannel1 = NULL;
	ClientAPI::_audioChannel2 = NULL;
	ClientAPI::_audioChannel3 = NULL;

	Mix_FreeMusic(ClientAPI::mainMusic);
	ClientAPI::mainMusic = NULL;

	SDL_DestroyRenderer(ClientAPI::mainRenderer);
	SDL_DestroyWindow(ClientAPI::mainWindow);
	ClientAPI::mainRenderer = NULL;
	ClientAPI::mainWindow = NULL;
}

void Game::Update()
{
	switch (gameStateManager.GetGameState())
	{
		case GameState::NONE:
			//Start of game, set to login screen
			gameStateManager.QueueChangeToGameState(startingState);
			break;
		case GameState::SCENE:
			int MouseX, MouseY;
			SDL_GetMouseState(&MouseX, &MouseY);
			scene->Update();
			break;
		default:
			gameStateManager.GetCurrentMenu()->Update();
			break;
	}
}

void Game::Draw()
{
	switch (gameStateManager.GetGameState())
	{
		case GameState::NONE:
			break;
		case GameState::SCENE:
			scene->Draw();
			break;
		default:
			gameStateManager.GetCurrentMenu()->Draw(ClientAPI::mainRenderer);
			break;
	}
}

void Game::Exit()
{
	GameIsRunning = false;
}