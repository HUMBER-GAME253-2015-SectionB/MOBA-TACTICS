//Author:	Mathieu Violette
//Date:		3/26/2015(MV)

#ifndef __TEXTSPRITE_H_INCLUDED__
#define __TEXTSPRITE_H_INCLUDED__

#include "Sprite.h"

class TextSprite : public Sprite
{
protected:
	std::string label;
	SDL_Color labelColor, shadowColor;
	float labelScale;
	SDL_Rect textDimensions;
	void ResizeTextDimensions();
	void ReCreateTextTexture();
	TTF_Font* font;
	bool hasShadow;
	SDL_Rect* GetShadowRect();
public:	
	SDL_Texture *Text, *Shadow;
	std::string& GetText();
	float GetTextScale();
	SDL_Color& GetTextColor();
	void SetText(const char*), SetTextColor(SDL_Color&), SetTextScale(float);
	void SetShadow(bool useShadow);

	TextSprite();
	TextSprite(const char* text, SDL_Rect& dimensions, SDL_Renderer* ren, TTF_Font* _font, bool _hasShadow = true, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);
	~TextSprite();

	TextSprite(SDL_Color& colour, SDL_Renderer* ren, SDL_Rect& dimensions, TTF_Font* _font, bool _hasShadow = true, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);
	TextSprite(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, TTF_Font* _font, bool _hasShadow = true, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);

	void Initialize(int width, int height, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect);
	virtual void Draw(SDL_Renderer*);
};

#endif