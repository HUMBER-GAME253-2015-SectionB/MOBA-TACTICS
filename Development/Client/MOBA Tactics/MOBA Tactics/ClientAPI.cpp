//Author:	David Vo, Mathieu Violette, Nicholas Higa
//Date:		2/23/2015(DV), 3/8/2015(MV), 3/18/2015(MV), 3/30/2015(NH)
//			4/6/2015 (NH), 4/8/2015(NH), 4/12/2015(NH)

#include "ClientAPI.h"

#include "Character.h"
#include "TileMap.h"
#include "Camera.h"
#include "Profile.h"
#include "Player.h"
#include "Archer.h"
#include "Warrior.h"
#include "Rogue.h"

SDL_Window* ClientAPI::mainWindow = NULL;
SDL_Renderer* ClientAPI::mainRenderer = NULL;
SDL_Surface* ClientAPI::mainSurface = NULL;

Mix_Music* ClientAPI::mainMusic = NULL;
Mix_Chunk* ClientAPI::_audioChannel = NULL;
Mix_Chunk* ClientAPI::_audioChannel1 = NULL;
Mix_Chunk* ClientAPI::_audioChannel2 = NULL;
Mix_Chunk* ClientAPI::_audioChannel3 = NULL;

Uint32 ClientAPI::elaspedTime = 0;

TileMap* ClientAPI::tileMap;
Camera* ClientAPI::camera;
vector<Player*> ClientAPI::players;
vector<Character*> ClientAPI::allCharacters;

int ClientAPI::currentPlayer;

Colors::Colors()
{
	White = ClientAPI::createColor(255, 255, 255, 255);
	Red = ClientAPI::createColor(255, 0, 0, 255);
	Black = ClientAPI::createColor(0, 0, 0, 255);
	Blue = ClientAPI::createColor(0, 0, 255, 255);
	Light_Blue = ClientAPI::createColor(0, 0, 155, 255);
	Green = ClientAPI::createColor(0, 255, 0, 255);
	Purple = ClientAPI::createColor(51, 0, 102, 255);
	Grey = ClientAPI::createColor(50, 50, 50, 255);
	Light_Grey = ClientAPI::createColor(150, 150, 150, 255);
}
Colors ClientAPI::Color = Colors();

void Fonts::Init_Fonts()
{
	Ostrich_Regular_20 = ClientAPI::createFont("../Assets/Font/ostrich-regular.ttf", 20);
	Ostrich_Regular_36 = ClientAPI::createFont("../Assets/Font/ostrich-regular.ttf", 36);
	Ostrich_Regular_72 = ClientAPI::createFont("../Assets/Font/ostrich-regular.ttf", 72);
	Ostrich_Regular_100 = ClientAPI::createFont("../Assets/Font/ostrich-regular.ttf", 100);
	Ostrich_Regular_200 = ClientAPI::createFont("../Assets/Font/ostrich-regular.ttf", 200);

	Ostrich_Bold_20 = ClientAPI::createFont("../Assets/Font/ostrich-black.ttf", 20);
	Ostrich_Bold_36 = ClientAPI::createFont("../Assets/Font/ostrich-black.ttf", 36);
	Ostrich_Bold_72 = ClientAPI::createFont("../Assets/Font/ostrich-black.ttf", 72);
	Ostrich_Bold_100 = ClientAPI::createFont("../Assets/Font/ostrich-black.ttf", 100);
	Ostrich_Bold_200 = ClientAPI::createFont("../Assets/Font/ostrich-black.ttf", 200);

	Droid_Regular_20 = ClientAPI::createFont("../Assets/Font/DroidSans.ttf", 20);
	Droid_Regular_36 = ClientAPI::createFont("../Assets/Font/DroidSans.ttf", 36);
	Droid_Regular_72 = ClientAPI::createFont("../Assets/Font/DroidSans.ttf", 72);
	Droid_Regular_100 = ClientAPI::createFont("../Assets/Font/DroidSans.ttf", 100);
	Droid_Regular_200 = ClientAPI::createFont("../Assets/Font/DroidSans.ttf", 200);

	Droid_Bold_20 = ClientAPI::createFont("../Assets/Font/DroidSans-Bold.ttf", 20);
	Droid_Bold_36 = ClientAPI::createFont("../Assets/Font/DroidSans-Bold.ttf", 36);
	Droid_Bold_72 = ClientAPI::createFont("../Assets/Font/DroidSans-Bold.ttf", 72);
	Droid_Bold_100 = ClientAPI::createFont("../Assets/Font/DroidSans-Bold.ttf", 100);
	Droid_Bold_200 = ClientAPI::createFont("../Assets/Font/DroidSans-Bold.ttf", 200);
}

void Fonts::Close_Fonts()
{
	TTF_CloseFont(Ostrich_Regular_20);
	TTF_CloseFont(Ostrich_Regular_36);
	TTF_CloseFont(Ostrich_Regular_72);
	TTF_CloseFont(Ostrich_Regular_100);
	TTF_CloseFont(Ostrich_Regular_200);

	TTF_CloseFont(Ostrich_Bold_20);
	TTF_CloseFont(Ostrich_Bold_36);
	TTF_CloseFont(Ostrich_Bold_72);
	TTF_CloseFont(Ostrich_Bold_100);
	TTF_CloseFont(Ostrich_Bold_200);


	TTF_CloseFont(Droid_Regular_20);
	TTF_CloseFont(Droid_Regular_36);
	TTF_CloseFont(Droid_Regular_72);
	TTF_CloseFont(Droid_Regular_100);
	TTF_CloseFont(Droid_Regular_200);

	TTF_CloseFont(Droid_Bold_20);
	TTF_CloseFont(Droid_Bold_36);
	TTF_CloseFont(Droid_Bold_72);
	TTF_CloseFont(Droid_Bold_100);
	TTF_CloseFont(Droid_Bold_200);
}
Fonts ClientAPI::Font = Fonts();

SDL_Texture* ClientAPI::createTexture(std::string _imgURL) {
	SDL_Surface* optimizedSurface = NULL;
	SDL_Texture* tempTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(_imgURL.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", _imgURL.c_str(), SDL_GetError());
	}
	else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, mainSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", _imgURL.c_str(), SDL_GetError());
		}

		tempTexture = SDL_CreateTextureFromSurface(mainRenderer, optimizedSurface);

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return tempTexture;
}

TTF_Font* ClientAPI::createFont(std::string path, int size)
{
	return TTF_OpenFont(path.c_str(), size);
}

SDL_Rect ClientAPI::createRectangle(int _x, int _y, int _width, int _height) {
	SDL_Rect tempRect;
	tempRect.x = _x;
	tempRect.y = _y;
	tempRect.w = _width;
	tempRect.h = _height;
	return tempRect;
}

Mix_Music* ClientAPI::loadMusic(std::string _musicURL) {
	Mix_Music* tempMusic = NULL;
	tempMusic = Mix_LoadMUS(_musicURL.c_str());
	if (tempMusic == NULL) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	return tempMusic;
}

Mix_Chunk* ClientAPI::loadSFX(std::string _sfxURL) {
	Mix_Chunk* tempSFX = NULL;
	tempSFX = Mix_LoadWAV(_sfxURL.c_str());
	if (tempSFX == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	return tempSFX;
}

TTF_Font* ClientAPI::loadFont(std::string _fontURL, int _fontSize) {
	TTF_Font* tempFont = NULL;
	tempFont = TTF_OpenFont(_fontURL.c_str(), _fontSize);
	if (tempFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	return tempFont;
}

int ClientAPI::StringToInt(const std::string &Text)
{
	std::stringstream ss(Text);
	int result;
	return ss >> result ? result : 0;
}

SDL_Color& ClientAPI::createColor(int r, int g, int b, int a)
{
	SDL_Color color = {r, g, b, a};
	return color;
}

Camera* ClientAPI::createCamera(vec2 pos, int width, int height, vec2 minBoundary, vec2 maxBoundary){
	Camera* tempCamera = new Camera(mainRenderer, pos, width, height, minBoundary, maxBoundary);
	return tempCamera;
}

TileMap* ClientAPI::createMap(char* _xmlFilePath, vec2 _origin, int _mainLayer, string highlightTexturePath, string hoverTexturePath) {
	TileMap* tempMap = new TileMap(_xmlFilePath, _origin, _mainLayer, highlightTexturePath, hoverTexturePath, mainRenderer);
	return tempMap;
}

/*Character* ClientAPI::createICharacter(char* spritePath, ITile* onTile) {
	ICharacter* tempCharacter = new Character(spritePath, onTile, mainRenderer);
	return tempCharacter;
}*/

Character* ClientAPI::createCharacter(char* spritePath, ITile* onTile)
{
	Character* tempCharacter = new Character(spritePath, onTile, mainRenderer);
	return tempCharacter;
}

Character* ClientAPI::createCharacter(char *spritePath, int row, int col)
{
	Character* tempCharacter = new Character(spritePath, row, col, mainRenderer);
	return tempCharacter;
}

Character* ClientAPI::createCharacterStats(char* spritePath, ITile* onTile, int _maxHealth, int _actionPoints,
	int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints)
{
	Character* tempCharacter = new Character(spritePath, onTile, _maxHealth, _actionPoints,
		_attackPower, _defense, _range, _speed, _experience, _level, _skillPoints, mainRenderer);
	return tempCharacter;
}

Character* ClientAPI::createCharacterStats(char* spritePath, int row, int col, int _maxHealth, int _actionPoints,
	int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints)
{
	Character* tempCharacter = new Character(spritePath, row, col, _maxHealth, _actionPoints,
		_attackPower, _defense, _range, _speed, _experience, _level, _skillPoints, mainRenderer);
	return tempCharacter;
}

Character* ClientAPI::createRogue(char *spritePath, int row, int col)
{
	return new Rogue(spritePath, row, col, mainRenderer);
}

Character* ClientAPI::createArcher(char *spritePath, int row, int col)
{
	return new Archer(spritePath, row, col, mainRenderer);
}

Character* ClientAPI::createWarrior(char *spritePath, int row, int col)
{
	return new Warrior(spritePath, row, col, mainRenderer);
}

void ClientAPI::addPlayer()
{
	PLAYERS.push_back(new Player());
}

void ClientAPI::addCharacter(Character* _character, int _playerIndex)
{
	PLAYERS[_playerIndex]->AddCharacter(_character);
	CHARACTERS.push_back(_character);
	CAMERA->AddToDrawList(_character);
}

int ClientAPI::GetNumPlayers()
{
	return PLAYERS.size();
}

int ClientAPI::GetCurrentPlayer()
{
	return currentPlayer;
}

void ClientAPI::SetCurrentPlayer(int val)
{
	currentPlayer = val;
}

void ClientAPI::CycleToNextPlayer()
{
	SetCurrentPlayer((GetCurrentPlayer() + 1) % GetNumPlayers());
}

Profile* ClientAPI::Login(std::string userName, std::string passWord)
{
	//talk to server
	//pass username & password
	if (userName != "" && passWord != "")
	{
		//on success
		//build profile
		//and return
		return new Profile(userName, SList<Character*>());
	}
	else
		//on fail, return nullptr
		return nullptr;
}