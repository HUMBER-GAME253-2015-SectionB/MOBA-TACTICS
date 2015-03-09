//Author:	David Vo, Mathieu Violette
//Date:		2/23/2015(DV), 3/8/2015(MV)

#include "ClientAPI.h"

SDL_Window* ClientAPI::mainWindow = NULL;
SDL_Renderer* ClientAPI::mainRenderer = NULL;
SDL_Surface* ClientAPI::mainSurface = NULL;

Mix_Music* ClientAPI::mainMusic = NULL;
Mix_Chunk* ClientAPI::_audioChannel = NULL;
Mix_Chunk* ClientAPI::_audioChannel1 = NULL;
Mix_Chunk* ClientAPI::_audioChannel2 = NULL;
Mix_Chunk* ClientAPI::_audioChannel3 = NULL;

TTF_Font* ClientAPI::mainFont = NULL;

Colors::Colors()
{
	White = ClientAPI::createColor(255, 255, 255, 255);
	Red = ClientAPI::createColor(255, 0, 0, 255);
	Black = ClientAPI::createColor(0, 0, 0, 255);
	Blue = ClientAPI::createColor(0, 0, 255, 255);
	Green = ClientAPI::createColor(0, 255, 0, 255);
	Purple = ClientAPI::createColor(51, 0, 102, 255);
}

Colors ClientAPI::Color = Colors();


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