//Author:	Mathieu Violette, Kees Vermeulen 
//Date:		3/8/2015(MV), 3/10/2015

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

void Button::SetSprite(Sprite* sprite)
{
	this->sprite = sprite;
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