#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Texture.h"
#include "TileMap.h"

enum GameState { StartingScreen, GameRunning, EndScreen };

static void LogSDLError(std::ostream &os, const std::string &msg);

int OnExecute();
bool OnInit();
void OnEvent(SDL_Event *event);
void OnLoop();
void OnRender();
void OnCleanup();

void UpdateInput(SDL_Event *event);
void UpdateSplashScreen(SDL_Event *event);

SDL_Window *win;
SDL_Renderer *ren;
SDL_Event *oldMouseState;

bool Running;
GameState gameState;

static Uint32 timeElapsed;
static Uint32 currentTime;
static Uint32 previousTime;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 600;	

Texture *texture;
TileMap *tiles;

float scale = 1.0f;
int scrollSpeed = 10;

//Overall game loop structure
int OnExecute()
{
	if (OnInit() == false) 
	{
		return -1;
	}

	SDL_Event event;

	while (Running) 
	{
		while (SDL_PollEvent(&event)) 
		{
			OnEvent(&event);
		}
		OnLoop();
		OnRender();
	}

	OnCleanup();

	return 0;
}

//Initialization
bool OnInit() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LogSDLError(std::cout, "SDL_Init");
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		LogSDLError(std::cout, "IMG_Init");
		return 1;
	}

	if (TTF_Init() != 0)
	{
		LogSDLError(std::cout, "TTF_Init");
		return 1;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return 1;
	}

	win = SDL_CreateWindow("Game Name", 100, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		LogSDLError(std::cout, "CreateWindow");
		return 1;
	} 

	ren = SDL_CreateRenderer(win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	texture = new Texture();
	//texture->LoadFromFile("./Assets/Images/IsoTiles.png", ren);

	//tiles = new TileMap("./Assets/Images/Tiles.png", 50, 50, 16, 12, 32, 32, ren);
	tiles = new TileMap("./Assets/XML_Files/IsoMap.tmx", 250, 50, "./Assets/Images/test.png", ren);
	//tiles->GetTileMap()[0][0][0]->Get
	tiles->GetTileMap()->at(0).at(0).at(1).SetIsHighlighted(true);
	tiles->GetTileMap()->at(3).at(2).at(2).SetIsHighlighted(true);
	tiles->GetTileMap()->at(3).at(3).at(3).SetIsHighlighted(true);
	return true;
}

//Whenever an event of some form occurs, this function is called. For example, mouse clicks/key presses.
void OnEvent(SDL_Event *event) 
{
	UpdateInput(event);
	UpdateSplashScreen(event);
}

//Equivalent to update function, but input is handled in OnEvent method
void OnLoop() 
{
	if (gameState == GameState::GameRunning)
	{
		previousTime = currentTime;
		currentTime = SDL_GetTicks();
		timeElapsed = currentTime - previousTime;

		//timeSinceLastSecond += timeElapsed / 1000.0f;
		tiles->Update(timeElapsed);
	}
}

void UpdateInput(SDL_Event *event)
{
	SDL_Event *newMouseState = event;
	if (gameState == GameState::EndScreen || gameState == GameState::StartingScreen)
	{
		//Exit game
		if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
		{
			Running = false;
		}
	}

	if (gameState == GameState::GameRunning)
	{
		if (event->type == SDL_KEYDOWN)
		{
			switch (event->key.keysym.sym)
			{
				case SDLK_UP: case SDLK_w:
					tiles->MoveMap(0, -scrollSpeed);
					break;
				case SDLK_DOWN: case SDLK_s:
					tiles->MoveMap(0, scrollSpeed);
					break;
				case SDLK_RIGHT: case SDLK_d:
					tiles->MoveMap(scrollSpeed, 0);
					break;
				case SDLK_LEFT: case SDLK_a:
					tiles->MoveMap(-scrollSpeed, 0);
					break;
				default:
					break;
			}
		}
		if (event->type == SDL_KEYUP)
		{
			switch (event->key.keysym.sym)
			{
			/*case SDLK_UP: case SDLK_w:
				tiles->MoveMap(0, -5);
				break;
			case SDLK_DOWN: case SDLK_s:
				tiles->MoveMap(0, 5);
				break;
			case SDLK_RIGHT: case SDLK_d:
				tiles->MoveMap(5, 0);
				break;
			case SDLK_LEFT: case SDLK_a:
				tiles->MoveMap(-5, 0);
				break;*/
			case SDLK_ESCAPE:
				Running = false;
			default:
				break;
			}
		}

		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			if (event->button.button == SDL_BUTTON_LEFT)
			{
			}

			if (event->button.button == SDL_BUTTON_RIGHT)
			{
			}

			if (newMouseState->button.button == SDL_BUTTON_RIGHT && oldMouseState->button.button == SDL_BUTTON_RIGHT)
			{
			}
			else
			{
				if (newMouseState->button.button == SDL_BUTTON_RIGHT)
				{
				}
				else if (oldMouseState->button.button == SDL_BUTTON_RIGHT)
				{
				}
			}
		}

		if (event->type == SDL_MOUSEWHEEL)
		{
			if (event->wheel.y > 0)
			{
				scale += 0.1f;
			}

			if (event->wheel.y < 0)
			{
				scale -= 0.1f;
			}
		}
	}
	oldMouseState = newMouseState;
}

//Equivalent to Draw function
void OnRender() 
{
	SDL_RenderClear(ren);
	if (gameState == GameState::StartingScreen)
	{
		//renderTexture(startScreen, ren, 0, 0);
	}
	else if (gameState == GameState::GameRunning)
	{
		SDL_Rect rec;
		rec.x = 64;
		rec.y = 32;
		rec.h = 32;
		rec.w = 32;

		//texture->Render(20, 20, &rec, ren);
		tiles->DrawMap(ren);
	}
	else
	{
		//renderTexture(endScreen, ren, 0, 0);
	}
	SDL_RenderSetScale(ren, scale, scale);

	SDL_RenderPresent(ren);
}

void UpdateSplashScreen(SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN && (gameState == GameState::StartingScreen || gameState == GameState::EndScreen))
	{
		if (event->key.keysym.sym == SDLK_SPACE)
		{
			//Start game
		}
	}
}

//Clean up memory
void OnCleanup() 
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) 
{
	Running = true;
	gameState = GameState::GameRunning;
	return OnExecute();
}

void LogSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}