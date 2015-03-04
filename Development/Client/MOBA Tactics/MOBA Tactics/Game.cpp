//Author:	Mathieu Violette
//Date:		3/22/2014(MV)

#include "Game.h"

const Uint8 *KeyState = SDL_GetKeyboardState(NULL);
int MouseX, MouseY;
Uint32 MouseState;
int PreviousMouseX, PreviousMouseY;
Uint32 PreviousMouseState;

int renWidth, renHeight;

Texture *texture;
TileMap *tiles;
Character *character;
vec3 charPos;

int StringToInt(const std::string &Text);

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
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
	SDL_Init(SDL_INIT_AUDIO);
	Window = nullptr;

	Window = SDL_CreateWindow("SDL 2.0.3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

	Renderer = nullptr;
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 400);
	SDL_GetRendererOutputSize(Renderer, &renWidth, &renHeight);

	//Initialize random
<<<<<<< HEAD
	srand(time(NULL));	
=======
	srand(time(NULL));
>>>>>>> origin/Client
}

void Game::LoadContent()
{
	texture = new Texture();
	tiles = new TileMap("../Assets/XML_Files/IsoMap.tmx", vec2(250, 50), "../Assets/Images/HighlightTile.png", Renderer);
	tiles->HighlightTile(1, 0, 0);
	tiles->SetHighlightColor(255, 0, 0);

	charPos = vec3(1, 0, 1);
	character = new Character("../Assets/Images/Character.png", tiles->GetTileAt(1, 0, 1), Renderer);
}

void Game::UnloadContent()
{

}

void Game::Update()
{
<<<<<<< HEAD
=======
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		OnEvent(&event);
	}

>>>>>>> origin/Client
	MouseState = SDL_GetMouseState(&MouseX, &MouseY);
	//KeyState = SDL_GetKeyboardState(NULL);	


	tiles->Update();
	character->Update();



	PreviousMouseState = MouseState;
	PreviousMouseX = MouseX;
	PreviousMouseY = MouseY;
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
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderPresent(Renderer);
}

void Game::Exit()
{
	GameIsRunning = false;
}

int StringToInt(const std::string &Text)
{
	std::stringstream ss(Text);
	int result;
	return ss >> result ? result : 0;
}