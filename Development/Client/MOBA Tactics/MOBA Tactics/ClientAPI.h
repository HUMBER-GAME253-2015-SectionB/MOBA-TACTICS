//Author:	David Vo, Mathieu Violette
//Date:		2/23/2015(DV), 3/8/2015(MV), 3/18/2015(MV)

#ifndef __CLIENTAPI_H_INCLUDED__
#define __CLIENTAPI_H_INCLUDED__

#define WIN32_LEAN_AND_MEAN

#define CAMERA ((Camera*)ClientAPI::camera)
#define TILEMAP ((TileMap*)ClientAPI::tileMap)
#define CHARACTER ((Character*)ClientAPI::character)

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

//Classes
#include "ITileMap.h"
#include "ICharacter.h"
#include "ICamera.h"

struct Colors
{
	SDL_Color White; 
	SDL_Color Red; 
	SDL_Color Black; 
	SDL_Color Blue; 
	SDL_Color Green; 
	SDL_Color Purple;
	SDL_Color Grey;

	Colors();
};

class ClientAPI
{

public:

	static Colors Color;

	static SDL_Color& createColor(int r, int g, int b, int a);

	static ITileMap* tileMap;
	static ICamera *camera;
	static ICharacter* character;

	static SDL_Window *mainWindow;
	static SDL_Renderer *mainRenderer;
	static SDL_Surface *mainSurface;

	static Mix_Music* mainMusic;
	static Mix_Chunk* _audioChannel;
	static Mix_Chunk* _audioChannel1;
	static Mix_Chunk* _audioChannel2;
	static Mix_Chunk* _audioChannel3;

	static TTF_Font* mainFont;

	static SDL_Texture* createTexture(std::string _imgURL);
	static SDL_Rect createRectangle(int _x, int _y, int _width, int _height);
	static Mix_Music* loadMusic(std::string _musicURL);
	static Mix_Chunk* loadSFX(std::string _sfxURL);
	static TTF_Font* loadFont(std::string _fontURL, int _fontSize);
	static int StringToInt(const std::string &Text); 

	static ICamera* createCamera(vec2 pos, int width, int height, vec2 minBoundary, vec2 maxBoundary);
	static ITileMap* createMap(char *xmlFilePath, vec2 _origin, string highlightTexturePath);
	static ICharacter* createCharacter(char* spritePath, ITile* onTile);
	static ICharacter* createCharacterStats(char* spritePath, ITile* onTile, int _maxHealth, int _actionPoints,
		int _attackPower, int _defense, int _range, int _speed, int _experience, int _level, int _skillPoints);
	
};
#endif