//Author:	Mathieu Violette
//Date:		3/30/2014(MV)

#include "Sprite.h"
#include "Game.h"

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

Vector2 Sprite::GetPosition()
{
	return position;
}
void Sprite::SetPosition(Vector2 value)
{
	if (UseOrigin)
	{
		rect.x = value.x - origin.x;
		rect.y = value.y - origin.y;
	}
	else
	{
		rect.x = value.x;
		rect.y = value.y;
	}
	position = value;
}


Vector2 Sprite::GetDimentions()
{
	return dimentions;
}
void Sprite::SetDimentions(Vector2 value)
{
	rect.w = value.x;
	rect.h = value.y;
	dimentions = value;
}


//===========================
//  CONSTRUCTOR / DESTRUCTOR
//===========================
Sprite::Sprite(SDL_Surface *image, SDL_Renderer* ren, Vector2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	Image = SDL_CreateTextureFromSurface(ren, image);

	UseOrigin = useOrigin;
	InitialScale = scale;
	SetPosition(pos);
	Rotation = 0;
	Vector2 dim = Vector2(image->w, image->h);
	SpriteEffect = spriteEffect;

	SetDimentions(dim);


	if (UseOrigin)
	{
		origin.x = (dim.x/2.0) * scale;
		origin.y = (dim.y/2.0) * scale;
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
	Vector2 v = Vector2(position.x - sprite->position.x, position.y - sprite->position.y);

	if (dimentions.x * Scale / 2.0 + sprite->dimentions.x * sprite->Scale / 2.0 >= sqrt((v.x * v.x) + (v.y * v.y)))
		return true;
	else
		return false;
}

void Sprite::SetScale(float value)
{
	rect.w = GetDimentions().x * value;
	rect.h = GetDimentions().y * value;
	Scale = value;
}