//Author:	Mathieu Violette
//Date:		3/22/2014(MV)

#include "Game.h"
#include "SDL_thread.h"
#include "TileMap.h"
#include "Character.h"

const Uint8 *KeyState = SDL_GetKeyboardState(NULL);
int MouseX, MouseY;
Uint32 MouseState;
int PreviousMouseX, PreviousMouseY;
Uint32 PreviousMouseState;

int renWidth, renHeight;

Texture *texture;
TileMap *tiles;
Character *character;

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

	texture = new Texture();
	tiles = new TileMap("../Assets/XML_Files/IsoMap.tmx", 250, 50, "../Assets/Images/test.png", Renderer);
	tiles->GetTileMap()->at(0).at(0).at(1).SetIsHighlighted(true);
	tiles->GetTileMap()->at(3).at(2).at(2).SetIsHighlighted(true);
	tiles->GetTileMap()->at(3).at(3).at(3).SetIsHighlighted(true);
	tiles->SetHighlightColor(100, 155, 255);

	character = new Character("../Assets/Images/Character.png", Renderer);
}

void Game::LoadContent()
{	
	
}

void Game::UnloadContent()
{

}

void Game::Update()
{
	MouseState = SDL_GetMouseState(&MouseX, &MouseY);
	//KeyState = SDL_GetKeyboardState(NULL);	

	PreviousMouseState = MouseState;
	PreviousMouseX = MouseX;
	PreviousMouseY = MouseY;

	tiles->Update();
}	

void Game::Draw()
{
	SDL_RenderClear(Renderer);
	/* DRAW CODE START */
	{
		tiles->DrawMap(Renderer);
		character->Draw(Renderer);
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