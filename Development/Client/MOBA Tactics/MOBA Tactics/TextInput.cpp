//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#include "TextInput.h"

TextInput::TextInput(SDL_Rect& dimentions)
{
	text = "";
	this->dimentions = dimentions;
	sprite = new Sprite("", dimentions, ClientAPI::mainRenderer);
}

TextInput::~TextInput()
{
	if (sprite != NULL)
		delete sprite;
}

void TextInput::Show()
{
	isVisible = true;
}

void TextInput::Hide()
{
	isVisible = false;
}

void TextInput::Draw()
{
	if (isVisible)
		sprite->Draw(ClientAPI::mainRenderer);
}

bool TextInput::CheckMouseCollision(int x, int y)
{
	return sprite->CollisionMouse(x, y);
}

void TextInput::Update()
{
	
}

void TextInput::SetText(char* _text)
{
	text = _text;

	delete sprite;
	sprite = nullptr;

	sprite = new Sprite(_text, dimentions, ClientAPI::mainRenderer);

}

char* TextInput::GetText() const
{
	return text.c_str;
}