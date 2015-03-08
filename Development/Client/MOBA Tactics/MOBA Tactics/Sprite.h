//Author:	Mathieu Violette, Nicholas Higa
//Date:		3/30/2014(MV), 3/7/2015(NH)

#ifndef __SPRITE_H_INCLUDED__
#define __SPRITE_H_INCLUDED__

#include "ClientAPI.h"
#include "glm/glm.hpp"

using namespace glm;

class Sprite
{
	protected:
		vec2 position, dimensions;
		SDL_Point origin;
		SDL_Rect rect;
	public:
		bool UseOrigin;
		float Rotation, Scale, InitialScale;
		SDL_Texture *Image;
		SDL_RendererFlip SpriteEffect;

		vec2 GetPosition(), GetDimensions();
		int GetWidth(), GetHeight();
		SDL_Texture* GetImage();
		SDL_Point GetOrigin();
		void SetOrigin(SDL_Point), SetPosition(vec2), SetDimensions(vec2);

		Sprite();
		Sprite(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect); 
		Sprite(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect);
		Sprite(std::string path, SDL_Renderer *ren, vec2 pos);
		void Initialize(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect);
		void Initialize(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect);
		~Sprite();
		virtual void Draw(SDL_Renderer*);
		virtual void Update(Uint32);
		virtual void Update(Uint32, SDL_Renderer*);
		virtual bool CollisionMouse(int mX, int mY);
		virtual bool RectCollisionSprite(Sprite*);
		virtual bool CircleCollisionSprite(Sprite*);
		void SetScale(float);
		void SetImage(SDL_Texture*);
		void SetBlendMode(SDL_BlendMode blending);
		void SetColor(Uint8 r, Uint8 g, Uint8 b);
		void SetAlpha(Uint8 alpha);

		static SDL_Rect new_Rect(int X, int Y, int W, int H);
};

#endif 