//Author:	Mathieu Violette
//Date:		3/22/2014(MV), 1/30/2015(MV)

#include "Game.h"

const Uint8 *KeyState = SDL_GetKeyboardState(NULL);
int MouseX, MouseY;
Uint32 MouseState;
int PreviousMouseX, PreviousMouseY;
Uint32 PreviousMouseState;
int renWidth, renHeight;

//Lab_02
SDL_Texture *Image, *textTexture;
SDL_Surface *Surface, *textSurface;
TTF_Font *font;


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


	SDL_Color fontColor = {0,0,0}; //Black
	std::stringstream textStream;
	textStream <<"Hello!";
	font = TTF_OpenFont("..\\Content\\arial.ttf",72);
	textSurface = TTF_RenderText_Solid(font,textStream.str().c_str(),fontColor);
	textTexture = SDL_CreateTextureFromSurface(Renderer,textSurface);
}

void Game::UnloadContent()
{
	//Lab_02
	SDL_FreeSurface(Surface);
	SDL_DestroyTexture(Image);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
}

void Game::Update()
{
	MouseState = SDL_GetMouseState(&MouseX, &MouseY);
	//KeyState = SDL_GetKeyboardState(NULL);	


	PreviousMouseState = MouseState;
	PreviousMouseX = MouseX;
	PreviousMouseY = MouseY;
}	

void Game::Draw()
{
	SDL_RenderClear(Renderer);
	/* DRAW CODE START */
	{
		//LAB_02
		//SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
		SDL_Rect rect = {294, 25, 435, 390};
		SDL_RenderCopy(Renderer, Image, NULL, &rect);

		SDL_Rect renderQuad = {425, 500,textSurface->w,textSurface->h};
		SDL_RenderCopy(Renderer, textTexture, NULL, &renderQuad);
		
		//Drawing lines with rectancles for some reason...
		SDL_SetRenderDrawColor(Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_Rect rect1 = {385, 490, 260, 3};
		SDL_RenderDrawRect(Renderer, &rect1);
		SDL_Rect rect2 = {400, 475, 3, 130};
		SDL_RenderDrawRect(Renderer, &rect2);
		SDL_Rect rect3 = {385, 590, 260, 3};
		SDL_RenderDrawRect(Renderer, &rect3);
		SDL_Rect rect4 = {630, 475, 3, 130};
		SDL_RenderDrawRect(Renderer, &rect4);
		
		//More efficient
		SDL_SetRenderDrawColor(Renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Renderer, 385, 491, 645, 491);
		SDL_RenderDrawLine(Renderer, 401, 475, 401, 605);
		SDL_RenderDrawLine(Renderer, 385, 591, 645, 591);
		SDL_RenderDrawLine(Renderer, 631, 475, 631, 605);

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