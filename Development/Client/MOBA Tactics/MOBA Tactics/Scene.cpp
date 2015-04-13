//Author:	David Vo, Nicholas Higa
//Date:		2/23/2015(DV), 3/30/2015(NH), 4/6/2015(NH), 4/12/2015(NH)

#include "Scene.h"
#include "Camera.h"
#include "TileMap.h"
#include "Character.h"
#include "Player.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::Init()
{
	minBound = vec2(-100, -100);
	maxBound = vec2(1524, 1268);
	ClientAPI::camera = ClientAPI::createCamera(vec2(0, 0), 1024, 768, minBound, maxBound);
	//camera = new Camera(ClientAPI::mainRenderer, vec2(0, 0), 1024, 768); 
	ClientAPI::addPlayer();
	ClientAPI::addPlayer();
	ClientAPI::SetCurrentPlayer((int)PlayerState::PLAYER_ONE);
}

void Scene::LoadContent()
{
	ClientAPI::tileMap = ClientAPI::createMap("../Assets/XML_Files/IsoMap.tmx", vec2(700, 300), 1, "../Assets/Images/HighlightTile.png", "../Assets/Images/HoverTile.png");
	//tiles = new TileMap("../Assets/XML_Files/IsoMap.tmx", vec2(400, 100), "../Assets/Images/HighlightTile.png", ClientAPI::mainRenderer);
	//tiles = new TileMap("../Assets/XML_Files/IsoMap.tmx", vec2(0, 0), "../Assets/Images/HighlightTile.png", ClientAPI::mainRenderer);
	TILEMAP->SetHighlightColor(255, 0, 0);
	TILEMAP->SetHoverColor(255, 0, 0);

	//	ClientAPI::character = ClientAPI::createCharacter("../Assets/Images/Character.png", ClientAPI::tileMap->GetTileAt(1, 0, 0));
	//character = new Character("../Assets/Images/Character.png", tiles->GetTileAt(1, 0, 0), ClientAPI::mainRenderer);
	CAMERA->AddToDrawList(TILEMAP);
	CAMERA->SetPosition(vec2(100, 100));

	Character *tmpChar0, *tmpChar1, *tmpChar2, *tmpChar3, *tmpChar4, *tmpChar5;
	//tmpChar0 = ClientAPI::createCharacter("../Assets/Images/Character.png", 6, 6);
	//ClientAPI::addCharacter(tmpChar0, 0);
	//tmpChar1 = ClientAPI::createCharacter("../Assets/Images/Character.png", 0, 1);
	//ClientAPI::addCharacter(tmpChar1, 0);
	//tmpChar2 = ClientAPI::createCharacter("../Assets/Images/Character.png", 1, 0);
	//ClientAPI::addCharacter(tmpChar2, 0);

	//tmpChar3 = ClientAPI::createCharacter("../Assets/Images/Character2.png", 8, 8);
	//ClientAPI::addCharacter(tmpChar3, 1);
	//tmpChar4 = ClientAPI::createCharacter("../Assets/Images/Character2.png", 8, 7);
	//ClientAPI::addCharacter(tmpChar4, 1);
	//tmpChar5 = ClientAPI::createCharacter("../Assets/Images/Character2.png", 7, 8);
	//ClientAPI::addCharacter(tmpChar5, 1);

	tmpChar0 = ClientAPI::createArcher("../Assets/Images/bArcher.png", 6, 6);
	ClientAPI::addCharacter(tmpChar0, 0);
	tmpChar1 = ClientAPI::createRogue("../Assets/Images/bRogue.png", 0, 1);
	ClientAPI::addCharacter(tmpChar1, 0);
	tmpChar2 = ClientAPI::createWarrior("../Assets/Images/bWarrior.png", 1, 0);
	ClientAPI::addCharacter(tmpChar2, 0);

	tmpChar3 = ClientAPI::createArcher("../Assets/Images/rArcher.png", 8, 8);
	ClientAPI::addCharacter(tmpChar3, 1);
	tmpChar4 = ClientAPI::createRogue("../Assets/Images/rRogue.png", 8, 7);
	ClientAPI::addCharacter(tmpChar4, 1);
	tmpChar5 = ClientAPI::createWarrior("../Assets/Images/rWarrior.png", 7, 8);
	ClientAPI::addCharacter(tmpChar5, 1);

	tmp1 = new Sprite("../Assets/Images/Character.png", ClientAPI::mainRenderer, vec2(maxBound.x - 21, minBound.y));
	CAMERA->AddToDrawList(tmp1);
	tmp2 = new Sprite("../Assets/Images/Character.png", ClientAPI::mainRenderer, vec2(minBound.x, minBound.y));
	CAMERA->AddToDrawList(tmp2);
	tmp3 = new Sprite("../Assets/Images/Character.png", ClientAPI::mainRenderer, vec2(minBound.x, maxBound.y - 37));
	CAMERA->AddToDrawList(tmp3);
	tmp4 = new Sprite("../Assets/Images/Character.png", ClientAPI::mainRenderer, vec2(maxBound.x - 21, maxBound.y - 37));
	CAMERA->AddToDrawList(tmp4);
}

void Scene::UnloadContent()
{
	delete ClientAPI::tileMap;
	delete ClientAPI::camera;
}

void Scene::Update()
{
	int MouseX, MouseY;
	SDL_GetMouseState(&MouseX, &MouseY);

	CAMERA->Update();
	TILEMAP->Update();

	vector<Character*> chars = PLAYERS[ClientAPI::GetCurrentPlayer()]->GetCharacterList();
	for (int i = 0; i < chars.size(); i++)
		chars[i]->Update();

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
}

void Scene::Draw()
{
	CAMERA->Draw(ClientAPI::mainRenderer);
}