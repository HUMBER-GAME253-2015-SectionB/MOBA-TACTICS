//Author:	David Vo, Mathieu Violette, Nicholas Higa
//Date:		2/23/2015(DV), 3/8/2015(MV), 3/18/2015(MV), 3/30/2015(NH)
//			4/6/2015 (NH), 4/8/2015(NH), 4/12/2015(NH)

#ifndef __CLIENTAPI_H_INCLUDED__
#define __CLIENTAPI_H_INCLUDED__

#define WIN32_LEAN_AND_MEAN

#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_net.h>

#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

//Classes
#include "ITileMap.h"
#include "ICharacter.h"
#include "ICamera.h"

class Profile;
class Player;
class Character;
class Camera;
class TileMap;
class Rogue;
class Archer;
class Warrior;

#define CAMERA ((Camera*)ClientAPI::camera)
#define TILEMAP ((TileMap*)ClientAPI::tileMap)
#define PLAYERS ClientAPI::players
#define CHARACTERS ClientAPI::allCharacters

struct Colors
{
	SDL_Color White; 
	SDL_Color Red; 
	SDL_Color Black; 
	SDL_Color Blue; 
	SDL_Color Light_Blue;
	SDL_Color Green; 
	SDL_Color Purple;
	SDL_Color Grey;
	SDL_Color Light_Grey;

	Colors();
};

struct Fonts
{
	TTF_Font *Ostrich_Regular_20, *Ostrich_Regular_36, *Ostrich_Regular_72, *Ostrich_Regular_100, *Ostrich_Regular_200;
	TTF_Font *Ostrich_Bold_20, *Ostrich_Bold_36, *Ostrich_Bold_72, *Ostrich_Bold_100, *Ostrich_Bold_200;

	TTF_Font *Droid_Regular_20, *Droid_Regular_36, *Droid_Regular_72, *Droid_Regular_100, *Droid_Regular_200;
	TTF_Font *Droid_Bold_20, *Droid_Bold_36, *Droid_Bold_72, *Droid_Bold_100, *Droid_Bold_200;
	
	void Init_Fonts();
	void Close_Fonts();
};

class ClientAPI
{

public:

	static Colors Color;
	static Fonts Font;
	static Uint32 elaspedTime;

	static SDL_Color& createColor(int r, int g, int b, int a);

	static TileMap* tileMap;
	static Camera *camera;
	static vector<Player*> players;
	static vector<Character*> allCharacters;

	static SDL_Window *mainWindow;
	static SDL_Renderer *mainRenderer;
	static SDL_Surface *mainSurface;

	static Mix_Music* mainMusic;
	static Mix_Chunk* _audioChannel;
	static Mix_Chunk* _audioChannel1;
	static Mix_Chunk* _audioChannel2;
	static Mix_Chunk* _audioChannel3;

	static SDL_Texture* createTexture(std::string _imgURL);
	static TTF_Font* createFont(std::string path, int size);
	static SDL_Rect createRectangle(int _x, int _y, int _width, int _height);
	static Mix_Music* loadMusic(std::string _musicURL);
	static Mix_Chunk* loadSFX(std::string _sfxURL);
	static TTF_Font* loadFont(std::string _fontURL, int _fontSize);
	static int StringToInt(const std::string &Text); 

	static Camera* createCamera(vec2 pos, int width, int height, vec2 minBoundary, vec2 maxBoundary);
	static TileMap* createMap(char *xmlFilePath, vec2 _origin, int _mainLayer, string highlightTexturePath, string hoverTexturePath);

	static Character* createCharacterStats(char* spritePath, ITile* onTile, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints);
	static Character* createCharacterStats(char* spritePath, int row, int col, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints);
	static Character* createCharacter(char* spritePath, ITile* onTile);
	static Character* createCharacter(char *spritePath, int row, int col);
	static Character* createRogue(char *spritePath, int row, int col);
	static Character* createArcher(char *spritePath, int row, int col);
	static Character* createWarrior(char *spritePath, int row, int col);

	static void addPlayer();
	static void addCharacter(Character*, int);

	static int currentPlayer;
	static int GetNumPlayers();
	static int GetCurrentPlayer();
	static void SetCurrentPlayer(int);
	static void CycleToNextPlayer();

	static Profile* Login(std::string userName, std::string passWord);

};

#endif