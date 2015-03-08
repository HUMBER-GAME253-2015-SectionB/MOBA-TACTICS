//Author:	Alejandro Zielinsky
//Date:		3/4/2015(AZ)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>

class GuiElement
{
private:
SDL_Rect box;

public:
GuiElement(int x,int y,int w,int h);
virtual void Update();
virtual void Draw();
virtual void show();
virtual void hide();
};

GuiElement::GuiElement(int x,int y,int w,int h)
{
 //Set the button attributes
 box.x = x;
 box.y = y;
 box.w = w;
 box.h = h;

}