//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "LoginButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

LoginButton::LoginButton()
{
	isVisible = true;

	SDL_Color black = {0x00, 0x00, 0x00, 0xFF};
	SDL_Color grey = {0x32, 0x32, 0x32, 0xFF};

	sprite = new Sprite(grey, ClientAPI::mainRenderer, ClientAPI::createRectangle(200, 400, 500, 150));
	sprite->SetText("Login");
	sprite->SetTextScale(0.3f);
}

LoginButton::~LoginButton()
{
	delete sprite;
}

void LoginButton::OnClick()
{

}

void LoginButton::OnHover()
{

}

void LoginButton::Update()
{

}