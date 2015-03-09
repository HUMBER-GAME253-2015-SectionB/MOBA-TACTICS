//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "LogoutButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

LogoutButton::LogoutButton()
{
	isVisible = true;
	
	sprite = new Sprite(ClientAPI::Color.Grey, ClientAPI::mainRenderer, ClientAPI::createRectangle(200, 200, 624, 150));
	sprite->SetText("Logout");
	sprite->SetTextScale(0.3f);
}

LogoutButton::~LogoutButton()
{
	delete sprite;
}

void LogoutButton::OnClick()
{
	Game::gameStateManager.ChangeToGameState(GameState::LOGIN);
}

void LogoutButton::OnHover()
{

}

void LogoutButton::Update()
{

}