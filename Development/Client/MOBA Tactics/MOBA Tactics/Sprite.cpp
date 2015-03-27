//Author:	Mathieu Violette, Nicholas Higa ,Alejandro Zielinsky
//Date:		3/30/2014(MV), 3/8/2014 (NH), 3/15/2015 (NH), 3/18/2015(AZ)

#include "Sprite.h"

//===========================
//		 PROPERTIES
//===========================

SDL_Point Sprite::GetOrigin()
{
	return origin;
}

void Sprite::SetOrigin(SDL_Point& value)
{
	origin = value;
}

vec2 Sprite::GetPosition()
{
	return position;
}

void Sprite::SetPosition(vec2& value)
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

void Sprite::SetDimensions(vec2& value)
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

//No parameter constructor, used for inheritance purposes.
//Assumes programmer will use Initialize method manually
Sprite::Sprite() { }

Sprite::Sprite(SDL_Color& colour, SDL_Renderer* ren, SDL_Rect& dimensions, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	imgSurface = IMG_Load("..\\Assets\\Images\\white1x1.png");
	Image = SDL_CreateTextureFromSurface(ren, imgSurface);

	SDL_SetTextureBlendMode(Image, SDL_BlendMode::SDL_BLENDMODE_NONE);
	SDL_SetTextureAlphaMod(Image, colour.a);	
	SDL_SetTextureColorMod(Image, colour.r, colour.g, colour.b);

	Initialize(dimensions.w, dimensions.h, vec2(dimensions.x, dimensions.y), useOrigin, scale, spriteEffect);
}

Sprite::Sprite(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	imgSurface = image;
	Image = SDL_CreateTextureFromSurface(ren, image);

	Initialize(image->w, image->h, pos, useOrigin, scale, spriteEffect);
}

Sprite::Sprite(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	imgSurface = IMG_Load(path.c_str());
	Image = SDL_CreateTextureFromSurface(ren, imgSurface);

	Initialize(imgSurface->w, imgSurface->h, pos, useOrigin, scale, spriteEffect);
}

void Sprite::Initialize(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	imgSurface = IMG_Load(path.c_str());
	Image = SDL_CreateTextureFromSurface(ren, imgSurface);

	Initialize(imgSurface->w, imgSurface->h, pos, useOrigin, scale, spriteEffect);
}

void Sprite::Initialize(int width, int height, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect)
{
	UseOrigin = useOrigin;
	InitialScale = scale;
	SetPosition(pos);
	Rotation = 0;
	vec2 dim = vec2(width, height);
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
}

Sprite::~Sprite()
{
	if (Image != nullptr)
		SDL_DestroyTexture(Image);

	if (imgSurface != nullptr)
		SDL_FreeSurface(imgSurface);
}

//===========================
//	   UTILITY METHODS
//===========================

void Sprite::Draw(SDL_Renderer* ren)
{
	if (Image != nullptr)
		SDL_RenderCopyEx(ren, Image, NULL, &rect, Rotation, &origin, SpriteEffect);
}

//Draw at different position than its set position
//Primary usage for Camera class
void Sprite::Draw(vec2 pos, SDL_Renderer *ren)
{
	SDL_Rect tmp = rect;
	tmp.x = pos.x;
	tmp.y = pos.y;

	if (Image != nullptr)
		SDL_RenderCopyEx(ren, Image, NULL, &tmp, Rotation, &origin, SpriteEffect);
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

bool Sprite::CollisionMouse(vec2 _origin, int mX, int mY)
{
	bool doesContain = false;

	if (mX >= _origin.x &&
		mX <= _origin.x + rect.w &&
		mY >= _origin.y &&
		mY <= _origin.y + rect.h)
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

void Sprite::ReCreateTexture()
{
	if (Image != nullptr)
		SDL_DestroyTexture(Image);

	Image = SDL_CreateTextureFromSurface(ClientAPI::mainRenderer, imgSurface);
}