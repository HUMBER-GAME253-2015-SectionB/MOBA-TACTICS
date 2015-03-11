//Author:	Mathieu Violette, Kees Vermeulen 
//Date:		3/8/2015(MV), 3/10/2015

#include "Button.h"

void Button::Show()
{
	isVisible = true;
}

void Button::Hide()
{
	isVisible = false;
}

void Button::Draw()
{
	if (isVisible)
		sprite->Draw(ClientAPI::mainRenderer);
}

bool Button::CheckMouseCollision(int x, int y)
{
	return sprite->CollisionMouse(x, y);
}

void Button::SetSprite(Sprite* sprite)
{
	this->sprite = sprite;
}

void Button::Update()
{
	if (buttonState == UNPRESSED)
	{
		if (isBeingHovered)
			SetSprite(spriteHover);
		else
			SetSprite(spriteUnpressed);
	}
	else if (buttonState == PRESSED)
	{
		if (isBeingHovered)
			SetSprite(spritePressed);
		else
			SetSprite(spriteUnpressed);
	}
		
}