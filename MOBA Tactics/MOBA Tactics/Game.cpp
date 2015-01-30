//Author:	Mathieu Violette
//Date:		3/22/2014(MV), 1/30/2015(MV)

#include "Game.h"
#include "SDL_thread.h"

const Uint8 *KeyState = SDL_GetKeyboardState(NULL);
int MouseX, MouseY;
Uint32 MouseState;
int PreviousMouseX, PreviousMouseY;
Uint32 PreviousMouseState;
int renWidth, renHeight;

//Lab_02
SDL_Texture *Image;
SDL_Surface *Surface;

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
	SDL_GetRendererOutputSize(Renderer, &renWidth, &renHeight);

	//Initialize random
	srand(time(NULL));
}

void Game::LoadContent()
{	
	//Lab_02
	Surface = IMG_Load("..\\Content\\Images\\humber_logo.jpg");
	Image = SDL_CreateTextureFromSurface(Renderer, Surface);
}

void Game::UnloadContent()
{
	//Lab_02
	SDL_FreeSurface(Surface);
	SDL_DestroyTexture(Image);
}

void Game::Update()
{
	MouseState = SDL_GetMouseState(&MouseX, &MouseY);
	//KeyState = SDL_GetKeyboardState(NULL);	
}	

void Game::Draw()
{
	SDL_RenderClear(Renderer);
	/* DRAW CODE START */
	{
		//LAB_02
		SDL_Rect *rect = new SDL_Rect();
		rect->w = 435; rect->h = 390; rect->x = 294; rect->y = 189; 
		SDL_RenderCopy(Renderer, Image, NULL, rect);
		delete rect;
	}
	/* DRAW CODE END */
	SDL_SetRenderDrawColor(Renderer,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderPresent(Renderer);
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