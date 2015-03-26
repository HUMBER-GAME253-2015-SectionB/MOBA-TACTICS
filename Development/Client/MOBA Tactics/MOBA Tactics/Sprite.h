//Author:	Mathieu Violette, Nicholas Higa, Alejandro Zielinsky
//Date:		3/30/2014(MV), 3/7/2015(NH), 3/15/2015 (NH), 3/18/2015(AZ)

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
		void SetOrigin(SDL_Point&), SetPosition(vec2&), SetDimensions(vec2&);

		Sprite();
		Sprite(SDL_Color& colour, SDL_Renderer* ren, SDL_Rect& dimensions, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);
		Sprite(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE); 
		Sprite(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);
		void Initialize(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);
		void Initialize(int width, int height, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect);
		virtual ~Sprite();
		virtual void Draw(vec2 pos, SDL_Renderer *ren);
		virtual void Draw(SDL_Renderer*);
		virtual void Update(Uint32);
		virtual void Update(Uint32, SDL_Renderer*);
		virtual bool CollisionMouse(vec2 _origin, int mX, int mY); //When sprite is drawn at a position differen than its field
		virtual bool CollisionMouse(int mX, int mY);
		virtual bool RectCollisionSprite(Sprite*);
		virtual bool CircleCollisionSprite(Sprite*);
		void SetScale(float);
		void SetImage(SDL_Texture*);
		void SetBlendMode(SDL_BlendMode blending);
		void SetColor(Uint8 r, Uint8 g, Uint8 b);
		void SetAlpha(Uint8 alpha);
};

#endif 