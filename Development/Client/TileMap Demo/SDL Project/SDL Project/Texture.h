#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

//Texture wrapper class
class Texture
{
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool LoadFromFile(std::string path, SDL_Renderer *ren);

	//Deallocates texture
	void Free();

	//Renders texture at given point
	void Render(int x, int y, SDL_Rect* clip, SDL_Renderer* ren);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

private:
	//The actual hardware texture
	SDL_Texture* texture;

	//Image dimensions
	int width;
	int height;
};

#endif