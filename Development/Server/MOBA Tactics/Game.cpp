//Author:	Mathieu Violette
//Date:		3/22/2014(MV)

#include "Game.h"
#include "SDL_thread.h"

const Uint8 *KeyState = SDL_GetKeyboardState(NULL);

int StringToInt(const std::string &Text );

Game::Game()
{
	GameIsRunning = true;
	elaspedTime = 0;
}

Game::~Game()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDLNet_Quit();
	SDL_Quit();
}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();
	Mix_Init(MIX_INIT_MP3|MIX_INIT_OGG);
	SDL_Init(SDL_INIT_AUDIO);
	Window = nullptr;

	Window = SDL_CreateWindow("SDL 2.0.3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

	Renderer = nullptr;
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	Mix_OpenAudio(44100,AUDIO_S16SYS,2,400);

	//Initialize random
	srand(time(NULL));
}

void Game::LoadContent()
{	
	
}

void Game::UnloadContent()
{

}

void Game::Update()
{

}	

void Game::Exit()
{
	GameIsRunning = false;
}

int StringToInt(const std::string &Text )
{                              
	std::stringstream ss(Text);
	int result;
	return ss >> result ? result : 0;
}