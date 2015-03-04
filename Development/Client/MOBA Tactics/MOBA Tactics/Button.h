//Author:	Alejandro Zielinsky
//Date:		3/4/2015(AZ)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>

class Button
{
private:
SDL_Rect box;  

public:
Button( int x, int y, int w, int h );
void onClick();
void show();

};

Button::Button( int x, int y, int w, int h )
{
    //Set the button attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
}

void Button::onClick()
{

}

void Button::show()
{



}
