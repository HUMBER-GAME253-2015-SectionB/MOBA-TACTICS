//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#include "Label.h"

Label::Label(std::string _text, SDL_Rect& dimentions)
{
	text = _text;
	this->dimentions = dimentions;
	sprite = new Sprite(text.c_str, dimentions, ClientAPI::mainRenderer);
}


Label::~Label()
{
	if (sprite != NULL)
		delete sprite;
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
		sprite->Draw(ClientAPI::mainRenderer);
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

	sprite = new Sprite(_text, dimentions, ClientAPI::mainRenderer);

}

char* Label::GetText() const
{
	return text.c_str;
}