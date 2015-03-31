//Author:	David Vo, Nicholas Higa
//Date:		2/23/2015(DV), 3/30/2015(NH)

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
}

void Scene::LoadContent()
{
	ClientAPI::tileMap = ClientAPI::createMap("../Assets/XML_Files/IsoMap.tmx", vec2(700, 300), "../Assets/Images/HighlightTile.png");
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

void Scene::UnloadContent()
{
	delete ClientAPI::tileMap;
	delete ClientAPI::character;
	delete ClientAPI::camera;
}

void Scene::Update()
{
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
}

void Scene::Draw()
{
	CAMERA->Draw(ClientAPI::mainRenderer);
}