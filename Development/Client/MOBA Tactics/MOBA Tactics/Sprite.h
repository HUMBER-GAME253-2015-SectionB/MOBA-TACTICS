//Author:	Mathieu Violette
//Date:		3/30/2014(MV)

#ifndef __SPRITE_H_INCLUDED__
#define __SPRITE_H_INCLUDED__

#include "Game.h"

struct Vector2
{
	float x;
	float y;

	Vector2(float _x = 0, float _y = 0)
	{
		x = _x;
		y = _y;
	}

};

class Sprite
{
	protected:
		Vector2 position, dimentions;
		SDL_Point origin;
		SDL_Rect rect;
	public:
		bool UseOrigin;
		float Rotation, Scale, InitialScale;
		SDL_Texture *Image;
		SDL_RendererFlip SpriteEffect;

		Vector2 GetPosition(), GetDimentions();
		SDL_Point GetOrigin();
		void SetOrigin(SDL_Point), SetPosition(Vector2), SetDimentions(Vector2);

		Sprite();
		Sprite(SDL_Surface *image, SDL_Renderer* ren, Vector2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect); 
		~Sprite();
		virtual void Draw(SDL_Renderer*);
		virtual void Update(Uint32);
		virtual void Update(Uint32, SDL_Renderer*);
		virtual bool CollisionMouse(int mX, int mY);
		virtual bool RectCollisionSprite(Sprite*);
		virtual bool CircleCollisionSprite(Sprite*);
		void SetScale(float);

		static SDL_Rect new_Rect(int X, int Y, int W, int H);
};

#endif 