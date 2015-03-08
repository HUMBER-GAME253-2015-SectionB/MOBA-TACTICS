//Author:	Mathieu Violette, Nicholas Higa
//Date:		3/30/2014(MV), 3/8/2014 (NH)

#include "Sprite.h"

SDL_Rect Sprite::new_Rect(int X, int Y, int W, int H)
{
	SDL_Rect _rect;
	_rect.x = X;
	_rect.y = Y;
	_rect.w = W;
	_rect.h = H;
	return _rect;
}

//===========================
//		 PROPERTIES
//===========================

SDL_Point Sprite::GetOrigin()
{
	return origin;
}

void Sprite::SetOrigin(SDL_Point value)
{
	origin = value;
}

vec2 Sprite::GetPosition()
{
	return position;
}

void Sprite::SetPosition(vec2 value)
{
	if (UseOrigin)
	{
		rect.x = (int)value.x - (int)origin.x;
		rect.y = (int)value.y - (int)origin.y;
	}
	else
	{
		rect.x = (int)value.x;
		rect.y = (int)value.y;
	}
	position = value;
}

vec2 Sprite::GetDimensions()
{
	return dimensions;
}

void Sprite::SetDimensions(vec2 value)
{
	rect.w = (int)value.x;
	rect.h = (int)value.y;
	dimensions = value;
}

int Sprite::GetWidth()
{
	return (int)GetDimensions().x;
}

int Sprite::GetHeight()
{
	return (int)GetDimensions().y;
}

SDL_Texture* Sprite::GetImage()
{
	return Image;
}

void Sprite::SetImage(SDL_Texture* _image)
{
	Image = _image;
}


//===========================
//  CONSTRUCTOR / DESTRUCTOR
//===========================
Sprite::Sprite(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	Initialize(image, ren, pos, useOrigin, scale, spriteEffect);
}

Sprite::Sprite(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	Initialize(path, ren, pos, useOrigin, scale, spriteEffect);
}

//Constructor with minimal parameters
Sprite::Sprite(std::string path, SDL_Renderer *ren, vec2 pos)
{
	Initialize(path, ren, pos, false, 1.0f, SDL_FLIP_NONE);
}

void Sprite::Initialize(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	Initialize(loadedSurface, ren, pos, useOrigin, scale, spriteEffect);
}

void Sprite::Initialize(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	Image = SDL_CreateTextureFromSurface(ren, image);

	UseOrigin = useOrigin;
	InitialScale = scale;
	SetPosition(pos);
	Rotation = 0;
	vec2 dim = vec2(image->w, image->h);
	SpriteEffect = spriteEffect;

	SetDimensions(dim);

	if (UseOrigin)
	{
		origin.x = (int)((dim.x / 2.0) * scale);
		origin.y = (int)((dim.y / 2.0) * scale);
	}
	else
	{
		origin.x = 0;
		origin.y = 0;
	}

	SetScale(scale);

	SDL_FreeSurface(image);
}

Sprite::~Sprite()
{
	if (Image != NULL)
		SDL_DestroyTexture(Image);
}

//===========================
//	   UTILITY METHODS
//===========================

void Sprite::Draw(SDL_Renderer* ren)
{
	SDL_RenderCopyEx(ren, Image, NULL, &rect, Rotation, &origin, SpriteEffect);
}

void Sprite::Update(Uint32 elaspedTime)
{
	
}

void Sprite::Update(Uint32 elaspedTime, SDL_Renderer* ren)
{
	
}

bool Sprite::CollisionMouse(int mX, int mY)
{
	bool doesContain = false;

	if (mX >= rect.x &&
		mX <= rect.x + rect.w &&
		mY >= rect.y &&
		mY <= rect.y + rect.h)
			doesContain = true;

	return doesContain;
}

bool Sprite::RectCollisionSprite(Sprite* sprite)
{
	bool doesIntersect = false;

	if (
		//Sides
		(
			(sprite->rect.x >= rect.x &&
			sprite->rect.x <= rect.w + rect.x)
			&&
			(sprite->rect.y >= rect.y &&
			sprite->rect.y <= rect.h + rect.y)
		)
		||
		(
			(sprite->rect.x + sprite->rect.w >= rect.x &&
			sprite->rect.x + sprite->rect.w <= rect.w + rect.x)
			&&
			(sprite->rect.y >= rect.y &&
			sprite->rect.y <= rect.h + rect.y)
		)
		||
		(
			(sprite->rect.x + sprite->rect.w >= rect.x &&
			sprite->rect.x + sprite->rect.w <= rect.w + rect.x)
			&&
			(sprite->rect.y + sprite->rect.h >= rect.y &&
			sprite->rect.y + sprite->rect.h <= rect.h + rect.y)
		)
		||
		(
			(sprite->rect.x >= rect.x &&
			sprite->rect.x  <= rect.w + rect.x)
			&&
			(sprite->rect.y + sprite->rect.h >= rect.y &&
			sprite->rect.y + sprite->rect.h <= rect.h + rect.y)
		)
		||
		(
			(sprite->rect.x < rect.x &&
			sprite->rect.x + sprite->rect.w > rect.w + rect.x)
			&&
			(
				(sprite->rect.y + sprite->rect.h >= rect.y &&
				sprite->rect.y + sprite->rect.h <= rect.h + rect.y)
				||
				(sprite->rect.y >= rect.y &&
				sprite->rect.y <= rect.h + rect.y)
			)
		)
		||
		(
			(sprite->rect.y < rect.y &&
			sprite->rect.y + sprite->rect.h > rect.h + rect.y)
			&&
			(
				(sprite->rect.x + sprite->rect.w >= rect.x &&
				sprite->rect.x + sprite->rect.w <= rect.w + rect.x)
				||
				(sprite->rect.x >= rect.x &&
				sprite->rect.x <= rect.w + rect.x)
			)
		)
		||
		(
			sprite->rect.y < rect.y &&
			sprite->rect.y + sprite->rect.h > rect.h + rect.y &&
			sprite->rect.x < rect.x &&
			sprite->rect.x + sprite->rect.w > rect.w + rect.x
		))
			doesIntersect = true;


	return doesIntersect;
}


bool Sprite::CircleCollisionSprite(Sprite* sprite)
{
	vec2 v = vec2(position.x - sprite->position.x, position.y - sprite->position.y);

	if (dimensions.x * Scale / 2.0 + sprite->dimensions.x * sprite->Scale / 2.0 >= sqrt((v.x * v.x) + (v.y * v.y)))
		return true;
	else
		return false;
}

void Sprite::SetScale(float value)
{
	rect.w = (int)((float)GetDimensions().x * value);
	rect.h = (int)((float)GetDimensions().y * value);
	Scale = value;
}

void Sprite::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(Image, blending);
}

void Sprite::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(Image, r, g, b);
}

void Sprite::SetAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(Image, alpha);
}