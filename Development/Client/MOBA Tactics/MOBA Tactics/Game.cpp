//Author:	Mathieu Violette
//Date:		3/22/2014(MV), 3/4/2015(MV)

#include "Game.h"

#include "Camera.h"
#include "TileMap.h"
#include "Character.h"

//FOR DEBUGGING: SWITCH TO DIFFERENT STARTING STATE
GameState startingState = GameState::SPLASH;
//GameState startingState = GameState::SCENE;

Game::Game()
{
	GameIsRunning = true;
	elaspedTime = 0;

	eventManager.KeyState = SDL_GetKeyboardState(NULL);
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
	minBound = vec2(-100, -100);
	maxBound = vec2(1524, 1268);
	ClientAPI::camera = ClientAPI::createCamera(vec2(0, 0), 1024, 768, minBound, maxBound);
	//camera = new Camera(ClientAPI::mainRenderer, vec2(0, 0), 1024, 768); 

	ClientAPI::Font.Init_Fonts();

	//Initialize random
	srand(time(NULL));	
}

void Game::LoadContent()
{
	ClientAPI::tileMap = ClientAPI::createMap("../Assets/XML_Files/IsoMap.tmx", vec2(400, 100), "../Assets/Images/HighlightTile.png");
	//tiles = new TileMap("../Assets/XML_Files/IsoMap.tmx", vec2(400, 100), "../Assets/Images/HighlightTile.png", ClientAPI::mainRenderer);
	//tiles = new TileMap("../Assets/XML_Files/IsoMap.tmx", vec2(0, 0), "../Assets/Images/HighlightTile.png", ClientAPI::mainRenderer);
	TILEMAP->SetHighlightColor(255, 0, 0);

	ClientAPI::character = ClientAPI::createCharacter("../Assets/Images/Character.png", ClientAPI::tileMap->GetTileAt(1, 0, 0));
	//character = new Character("../Assets/Images/Character.png", tiles->GetTileAt(1, 0, 0), ClientAPI::mainRenderer);
	CAMERA->AddToDrawList(TILEMAP);
	CAMERA->AddToDrawList(CHARACTER);
	CAMERA->SetPosition(vec2(100, 100));

	tmp1 = new Sprite("../Assets/Images/Character.png", ClientAPI::mainRenderer, vec2(maxBound.x - 21, minBound.y));
	CAMERA->AddToDrawList(tmp1);
	tmp2 = new Sprite("../Assets/Images/Character.png", ClientAPI::mainRenderer, vec2(minBound.x, minBound.y));
	CAMERA->AddToDrawList(tmp2);
	tmp3 = new Sprite("../Assets/Images/Character.png", ClientAPI::mainRenderer, vec2(minBound.x, maxBound.y - 37));
	CAMERA->AddToDrawList(tmp3);
	tmp4 = new Sprite("../Assets/Images/Character.png", ClientAPI::mainRenderer, vec2(maxBound.x - 21, maxBound.y - 37));
	CAMERA->AddToDrawList(tmp4);
}

void Game::UnloadContent()
{
	//End program

	delete ClientAPI::tileMap;
	delete ClientAPI::character;
	delete ClientAPI::camera;
	
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

			CAMERA->Update();
			TILEMAP->Update();
			CHARACTER->Update();

			//This block of code can not be used within Event Manager because the 
			//Event manager does not handle cases where the mouse doesn't move. This
			//is because an event is only called when the mouse has moved for example.
			//This portion of code requires an update every tick instead of every 
			//mouse event.
			if (MouseX <= 30)
				CAMERA->MoveCamera(vec2(-30, 0));

			if (MouseX >= CAMERA->GetWidth() - 30)
				CAMERA->MoveCamera(vec2(30, 0));

			if (MouseY <= 30)
				CAMERA->MoveCamera(vec2(0, -30));

			if (MouseY >= CAMERA->GetHeight() - 30)
				CAMERA->MoveCamera(vec2(0, 30));

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
			CAMERA->Draw(ClientAPI::mainRenderer);
			//tiles->Draw(vec2(0, 0), ClientAPI::mainRenderer);
			//tiles->Draw(ClientAPI::mainRenderer);
			//tiles->DrawTile(vec2(0, 0), 1, 5, 5, ClientAPI::mainRenderer);
			//character->Draw(ClientAPI::mainRenderer);
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