#ifndef __HELPER_FUNCTIONS__
#define __HELPER_FUNCTIONS__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

namespace HelperFunctions
{
	static SDL_Texture* LoadTexture(const std::string &file, SDL_Renderer *ren);
	static void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	static void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect src, int x, int y);
	static SDL_Texture* RenderText(const std::string &message, const std::string &fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer);

	/*SDL_Texture* RenderText(const std::string &message, const std::string &fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer)
	{
		//Open the font
		TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
		if (font == nullptr){
			LogSDLError(std::cout, "TTF_OpenFont");
			return nullptr;
		}
		//We need to first render to a surface as that's what TTF_RenderText
		//returns, then load that surface into a texture
		SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
		if (surf == nullptr){
			TTF_CloseFont(font);
			LogSDLError(std::cout, "TTF_RenderText");
			return nullptr;
		}
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
		if (texture == nullptr){
			LogSDLError(std::cout, "CreateTexture");
		}
		//Clean up the surface and font
		SDL_FreeSurface(surf);
		TTF_CloseFont(font);
		return texture;
	}*/
}

#endif