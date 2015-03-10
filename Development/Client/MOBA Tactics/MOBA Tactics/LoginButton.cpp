//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "LoginButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

LoginButton::LoginButton()
{
	isVisible = true;
	isBeingHovered = false;

	spriteUnpressed = new Sprite(ClientAPI::Color.Purple, ClientAPI::mainRenderer, ClientAPI::createRectangle(200, 400, 624, 150));
	spriteUnpressed->SetText("Login Unpressed");
	spriteUnpressed->SetTextScale(0.6f);

	spritePressed = new Sprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, ClientAPI::createRectangle(200, 400, 624, 150));
	spritePressed->SetText("Login Pressed");
	spritePressed->SetTextScale(0.6f);

	spriteHover = new Sprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, ClientAPI::createRectangle(200, 400, 624, 150));
	spriteHover->SetText("Login Hover");
	spriteHover->SetTextScale(0.6f);

	buttonState = UNPRESSED;
	sprite = spriteUnpressed;
}

LoginButton::~LoginButton()
{
	delete spritePressed;
	delete spriteHover;
	delete spriteUnpressed;
}

void LoginButton::OnClick()
{
	Game::gameStateManager.ChangeToGameState(GameState::MAINMENU);
}

void LoginButton::OnHover()
{

}