//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "LogoutButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

LogoutButton::LogoutButton()
{
	isVisible = true;
	isBeingHovered = false;
	
	spriteUnpressed = new Sprite(ClientAPI::Color.Grey, ClientAPI::mainRenderer, ClientAPI::createRectangle(200, 200, 624, 150));
	spriteUnpressed->SetText("Logout Unpressed");
	spriteUnpressed->SetTextScale(0.6f);

	spritePressed = new Sprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, ClientAPI::createRectangle(200, 200, 624, 150));
	spritePressed->SetText("Logout Pressed");
	spritePressed->SetTextScale(0.6f);

	spriteHover = new Sprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, ClientAPI::createRectangle(200, 200, 624, 150));
	spriteHover->SetText("Logout Hover");
	spriteHover->SetTextScale(0.6f);

	buttonState = UNPRESSED;
	sprite = spriteUnpressed;
}

LogoutButton::~LogoutButton()
{
	delete spritePressed;
	delete spriteHover;
	delete spriteUnpressed;
}

void LogoutButton::OnClick()
{
	Game::gameStateManager.ChangeToGameState(GameState::LOGIN);
}

void LogoutButton::OnHover()
{

}
