//Author:	Mathieu Violette , Alejandro Zielinsky
//Date:		3/10/2015(MV), 3/18/2015(AZ)

#include "TextInput.h"

TextInput::TextInput(SDL_Rect& dimentions, TTF_Font* _font, int _maxCharacters)
{
	font = _font;
	text = "";
	maxCharacters = _maxCharacters;
	currentState = UNFOCUSED;
	this->dimentions = dimentions;

	spriteUnfocused = new TextSprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, dimentions, font, false);
	spriteFocused = new TextSprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, dimentions, font, false);

	Show();
	SelectSprite();
}

TextInput::~TextInput()
{
	if (spriteUnfocused != NULL)
		delete spriteUnfocused;
	if (spriteFocused != NULL)
		delete spriteFocused;

	font = nullptr;
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
		((TextSprite*)sprite)->Draw(ClientAPI::mainRenderer);
}

bool TextInput::CheckMouseCollision(int x, int y)
{
	return sprite->CollisionMouse(x, y);
}

void TextInput::Update()
{
	SelectSprite();
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

void TextInput::RedrawText()
{
	char* newText = new char[text.length() + 1];
	strcpy_s(newText, text.length() + 1, text.c_str());

	((TextSprite*)spriteFocused)->SetText(newText);
	((TextSprite*)spriteUnfocused)->SetText(newText);

	delete[] newText;
}

void TextInput::SetText(const char* _text)
{
	if (text.length() < maxCharacters)
	{
		text += _text;
		RedrawText();
	}
}

void TextInput::TextAction_Backspace()
{
	if (text.length() > 0)
	{
		text = text.substr(0, text.length() - 1);
		RedrawText();
	}
}

std::string TextInput::GetText() const
{
	return text;
}

void TextInput::SetSprite(Sprite* sprite)
{
	this->sprite = sprite;
}

void TextInput::SelectSprite()
{
	if (currentState == FOCUSED)
	{
		SetSprite(spriteFocused);
	}
	else if (currentState == UNFOCUSED)
	{
		SetSprite(spriteUnfocused);
	}
}

int TextInput::GetMaxCharacters() const
{
	return maxCharacters;
}

void TextInput::SetMaxCharacters(int newMax)
{
	if (text.length() > newMax)
	{
		text = text.substr(0, newMax);
		RedrawText();
	}
	maxCharacters = newMax;
}