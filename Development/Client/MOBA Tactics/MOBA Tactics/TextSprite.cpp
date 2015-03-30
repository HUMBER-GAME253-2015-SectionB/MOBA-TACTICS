//Author:	Mathieu Violette
//Date:		3/26/2015(MV)

#include "TextSprite.h"

//===========================
//		 PROPERTIES
//===========================

std::string& TextSprite::GetText()
{
	return label;
}

void TextSprite::SetText(const char* _text)
{
	label = _text;

	ReCreateTextTexture();

	ResizeTextDimensions();
}

SDL_Color& TextSprite::GetTextColor()
{
	return labelColor;
}

void TextSprite::SetTextColor(SDL_Color& colour)
{
	labelColor = colour;
	ReCreateTextTexture();
}

float TextSprite::GetTextScale()
{
	return labelScale;
}

void TextSprite::SetTextScale(float scale)
{
	labelScale = scale;
	ReCreateTextTexture();
}

//===========================
//  CONSTRUCTOR / DESTRUCTOR
//===========================

TextSprite::TextSprite(const char* text, SDL_Rect& dimensions, SDL_Renderer* ren, TTF_Font* _font, bool _hasShadow, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	font = _font;
	hasShadow = _hasShadow;

	//Make invisible background
	SDL_Surface* loadedSurface = IMG_Load("../Assets/Images/white1x1.png");
	Image = SDL_CreateTextureFromSurface(ren, loadedSurface);
	SDL_SetTextureAlphaMod(Image, 0);
	SDL_SetTextureBlendMode(Image, SDL_BlendMode::SDL_BLENDMODE_BLEND);

	Initialize(dimensions.w, dimensions.h, vec2(dimensions.x, dimensions.y), useOrigin, scale, spriteEffect);

	SetText(text);

	SDL_FreeSurface(loadedSurface);
}

TextSprite::TextSprite(SDL_Color& colour, SDL_Renderer* ren, SDL_Rect& dimensions, TTF_Font* _font, bool _hasShadow, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	font = _font;
	hasShadow = _hasShadow;

	SDL_Surface* loadedSurface = IMG_Load("../Assets/Images/white1x1.png");
	Image = SDL_CreateTextureFromSurface(ren, loadedSurface);

	SDL_SetTextureColorMod(Image, colour.r, colour.g, colour.b);
	SDL_SetTextureAlphaMod(Image, colour.a);
	SDL_SetTextureBlendMode(Image, SDL_BlendMode::SDL_BLENDMODE_NONE);

	Initialize(dimensions.w, dimensions.h, vec2(dimensions.x, dimensions.y), useOrigin, scale, spriteEffect);

	SDL_FreeSurface(loadedSurface);
}

TextSprite::TextSprite(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, TTF_Font* _font, bool _hasShadow, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	font = _font;
	hasShadow = _hasShadow;

	Image = SDL_CreateTextureFromSurface(ren, image);

	Initialize(image->w, image->h, pos, useOrigin, scale, spriteEffect);

	SDL_FreeSurface(image);
}

void TextSprite::Initialize(int width, int height, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	label = "";
	labelColor = ClientAPI::Color.Black;
	shadowColor = ClientAPI::Color.Black;
	SetTextScale(0.925f);

	Sprite::Initialize(width, height, pos, useOrigin, scale, spriteEffect);
}

TextSprite::~TextSprite()
{
	if (Image != NULL)
		SDL_DestroyTexture(Image);

	if (Text != NULL)
		SDL_DestroyTexture(Text);

	font = nullptr;
}

void TextSprite::Draw(SDL_Renderer* ren)
{
	Sprite::Draw(ren);

	if (hasShadow && Shadow != nullptr)
	{
		SDL_RenderCopyEx(ren, Shadow, NULL, GetShadowRect(), Rotation, &origin, SpriteEffect);
	}

	if (Text != nullptr)
	{
		SDL_RenderCopyEx(ren, Text, NULL, &textDimensions, Rotation, &origin, SpriteEffect);
	}
}

//===========================
//	   UTILITY METHODS
//===========================

void TextSprite::ResizeTextDimensions()
{
	//Text width & height
	int w, h, x, y;

	//Get width & height of text
	TTF_SizeText(font, label.c_str(), &w, &h);

	float scale = Scale * labelScale;
	int windowWidth, windowHeight;

	if (rect.x < 0 || rect.y < 0)
		SDL_GetWindowSize(ClientAPI::mainWindow, &windowWidth, &windowHeight);

	//if less than 0, center.
	if (rect.x < 0)
		x = (windowWidth - w)*.5f;
	else
		x = rect.x + ((dimensions.x * .5f) - (dimensions.x * scale * .5f));

	if (rect.y < 0)
		y = (windowHeight - h)*.5f;
	else
		y = rect.y + (dimensions.y - h)*.5f + dimensions.y*.05f;
	
	textDimensions = ClientAPI::createRectangle(x, y, w, h);
}

void TextSprite::ReCreateTextTexture()
{
	if (Text != nullptr)
		SDL_DestroyTexture(Text);

	if (hasShadow && Shadow != nullptr)
		SDL_DestroyTexture(Shadow);
	
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, label.c_str(), labelColor);
	Text = SDL_CreateTextureFromSurface(ClientAPI::mainRenderer, textSurface);
	SDL_FreeSurface(textSurface);

	if (hasShadow)
	{
		SDL_Surface* shadowSurface = TTF_RenderText_Solid(font, label.c_str(), shadowColor);
		Shadow = SDL_CreateTextureFromSurface(ClientAPI::mainRenderer, shadowSurface);
		SDL_FreeSurface(shadowSurface);
	}
}

void TextSprite::SetShadow(bool useShadow)
{
	if (hasShadow != useShadow)
	{
		hasShadow = useShadow;

		ReCreateTextTexture();
	}
}

SDL_Rect* TextSprite::GetShadowRect()
{
	return &ClientAPI::createRectangle(textDimensions.x + 2, textDimensions.y + 2, textDimensions.w, textDimensions.h);
}