//Author:	David Vo
//Date:		2/23/2014(DV)

#ifndef __CLIENTAPI_H_INCLUDED__
#define __CLIENTAPI_H_INCLUDED__

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
	SDL_Surface imageLoader(const char* _imgURL) {
		SDL_Surface *tempSurface = IMG_Load(_imgURL);
		//tempSurface = IMG_Load("..\\Content\\Images\\humber_logo.jpg");
		return *tempSurface;
	}

	SDL_Rect createRectangle(int _x, int _y, int _width, int _height) {
		SDL_Rect tempRect;
		tempRect.x = _x;
		tempRect.y = _y;
		tempRect.w = _width;
		tempRect.h = _height;
		return tempRect;
	}

	//SDL_Texture createTexture(SDL_Renderer* _renderer, SDL_Surface* _image) {
	//	SDL_Texture *tempTexture;
	//	tempTexture = SDL_CreateTextureFromSurface(_renderer, _image);
	//	return *tempTexture;
	//}

private:
	ClientAPI() {}
	~ClientAPI() {}
};
#endif