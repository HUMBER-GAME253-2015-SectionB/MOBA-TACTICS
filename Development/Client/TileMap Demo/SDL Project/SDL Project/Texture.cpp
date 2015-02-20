#include "Texture.h"

Texture::Texture()
{
	//Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	//Deallocate
	Free();
}

bool Texture::LoadFromFile(std::string path, SDL_Renderer *ren)
{
	//Get rid of preexisting texture
	Free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(texture, blending);
}

void Texture::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(texture, r, g, b);
}

void Texture::SetAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::Free()
{
	//Free texture if it exists
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

//Render image to screen that is the same pixel size as the texture
void Texture::Render(int x, int y, SDL_Rect *clip, SDL_Renderer *ren)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(ren, texture, clip, &renderQuad);
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}