//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#include "Label.h"

Label::Label(char* _text, SDL_Rect& dimentions, TTF_Font* _font)
{
	font = _font;
	isVisible = true;
	text = _text;
	this->dimentions = dimentions;
	sprite = new TextSprite(_text, dimentions, ClientAPI::mainRenderer, font);
}


Label::~Label()
{
	if (sprite != NULL)
		delete sprite;

	font = nullptr;
}

void Label::Show()
{
	isVisible = true;
}

void Label::Hide()
{
	isVisible = false;
}

void Label::Draw()
{
	if (isVisible)
		((TextSprite*)sprite)->Draw(ClientAPI::mainRenderer);
}

bool Label::CheckMouseCollision(int x, int y)
{
	return sprite->CollisionMouse(x, y);
}

void Label::Update()
{
			
}

void Label::SetText(char* _text)
{
	text = _text;

	delete sprite;
	sprite = nullptr;

	sprite = new TextSprite(_text, dimentions, ClientAPI::mainRenderer, font);

}

std::string Label::GetText() const
{
	return text;
}