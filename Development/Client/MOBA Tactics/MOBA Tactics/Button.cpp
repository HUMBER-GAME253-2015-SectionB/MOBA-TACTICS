//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

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

void Button::Update()
{
	if (buttonState == UNPRESSED)
	{
		if (isBeingHovered)
			sprite = spriteHover;
		else
			sprite = spriteUnpressed;
	}
	else if (buttonState == PRESSED)
	{
		if (isBeingHovered)
			sprite = spritePressed;
		else
			sprite = spriteUnpressed;
	}
		
}