//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "Button.h"

Button::Button()
{
	isVisible = true;
	isBeingHovered = false;
	buttonState = UNPRESSED;
}

Button::~Button()
{
	if (spritePressed != NULL)
		delete spritePressed;
	if (spriteHover != NULL)
		delete spriteHover;
	if (spriteUnpressed != NULL)
		delete spriteUnpressed;
}

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
	{
		SelectSprite();
		sprite->Draw(ClientAPI::mainRenderer);
	}
}

bool Button::CheckMouseCollision(int x, int y)
{
	return sprite->CollisionMouse(x, y);
}

void Button::Update()
{
	SelectSprite();	
}

void Button::SelectSprite()
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