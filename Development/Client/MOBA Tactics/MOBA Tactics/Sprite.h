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
		std::string label;
		SDL_Color labelColor;
		float labelScale;
	public:
		bool UseOrigin;
		float Rotation, Scale, InitialScale;
		SDL_Texture *Image, *Text;
		SDL_RendererFlip SpriteEffect;

		std::string& GetText();
		vec2 GetPosition(), GetDimensions();
		int GetWidth(), GetHeight();
		float GetTextScale();
		SDL_Texture* GetImage();
		SDL_Point GetOrigin();
		SDL_Color& GetTextColor();
		void SetOrigin(SDL_Point&), SetPosition(vec2&), SetDimensions(vec2&), SetText(const char*), SetTextColor(SDL_Color&), SetTextScale(float);

		Sprite();
		Sprite(const char* text, SDL_Rect& dimensions, SDL_Renderer* ren, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);
		Sprite(SDL_Color& colour, SDL_Renderer* ren, SDL_Rect& dimensions, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);
		Sprite(SDL_Surface *image, SDL_Renderer* ren, vec2 pos, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE); 
		Sprite(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);
		void Initialize(std::string path, SDL_Renderer* ren, vec2 pos, bool useOrigin = false, float scale = 1.0f, SDL_RendererFlip spriteEffect = SDL_FLIP_NONE);
		void Initialize(int width, int height, vec2 pos, bool useOrigin, float scale, SDL_RendererFlip spriteEffect);
		~Sprite();
		virtual void Draw(vec2 pos, SDL_Renderer *ren);
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
};

#endif 