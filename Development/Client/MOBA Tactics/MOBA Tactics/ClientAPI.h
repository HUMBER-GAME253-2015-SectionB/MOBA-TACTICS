//Author:	David Vo
//Date:		2/23/2015(DV)

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

class ClientAPI
{

public:

	static SDL_Window *mainWindow;
	static SDL_Renderer *mainRenderer;
	static SDL_Surface *mainSurface;

	static Mix_Music* mainMusic;
	static Mix_Chunk* _audioChannel;
	static Mix_Chunk* _audioChannel1;
	static Mix_Chunk* _audioChannel2;
	static Mix_Chunk* _audioChannel3;

	static TTF_Font* mainFont;

	static enum colorList
	{
		White, Red, Black, Blue, Green, Purple
	};

	static SDL_Texture* createTexture(std::string _imgURL);
	static SDL_Rect createRectangle(int _x, int _y, int _width, int _height);
	static Mix_Music* loadMusic(std::string _musicURL);
	static Mix_Chunk* loadSFX(std::string _sfxURL);
	static TTF_Font* loadFont(std::string _fontURL, int _fontSize);
	static int StringToInt(const std::string &Text);

private:
	ClientAPI() {}
	~ClientAPI() {}
};
#endif