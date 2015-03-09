//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "LoginButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

LoginButton::LoginButton()
{
	isVisible = true;

	sprite = new Sprite(ClientAPI::Color.Grey, ClientAPI::mainRenderer, ClientAPI::createRectangle(200, 400, 624, 150));
	sprite->SetText("Login");
	sprite->SetTextScale(0.3f);
}

LoginButton::~LoginButton()
{
	delete sprite;
}

void LoginButton::OnClick()
{
	Game::gameStateManager.ChangeToGameState(GameState::MAINMENU);
}

void LoginButton::OnHover()
{

}

void LoginButton::Update()
{

}