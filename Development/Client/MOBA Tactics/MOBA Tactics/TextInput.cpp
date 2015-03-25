//Author:	Mathieu Violette , Alejandro Zielinsky
//Date:		3/10/2015(MV), 3/18/2015(AZ)

#include "TextInput.h"

TextInput::TextInput(SDL_Rect& dimentions)
{
	text = "";
	currentState = TIS_UNPRESSED;
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

void TextInput::OnClick()
{
	setFocus(true);
}

void TextInput::setFocus(bool newVal)
{
	if(newVal)
	{
		hasFocus = true;
		SDL_StartTextInput();
	}
	else
	{
		hasFocus = false;
		SDL_StopTextInput();
	}

}


void TextInput::SetText(const char* _text)
{
	text = _text;

	delete sprite;
	sprite = nullptr;

	sprite = new Sprite(_text, dimentions, ClientAPI::mainRenderer);

}

std::string TextInput::GetText() const
{
	return text;
}