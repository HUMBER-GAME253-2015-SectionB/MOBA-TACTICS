//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "LoginButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

LoginButton::LoginButton()
{
	isVisible = true;
	isBeingHovered = false;

	//spriteUnpressed = new Sprite(ClientAPI::Color.Purple, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteUnpressed = new Sprite("../Assets/Images/Buttons/LoginBtnUp.png", ClientAPI::mainRenderer, vec2(100,600), false, 1.0f, SDL_FLIP_NONE);
	spriteUnpressed->SetColor(255,0,0);
	spriteUnpressed->SetTextScale(0.6f);

	//spritePressed = new Sprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spritePressed = new Sprite("../Assets/Images/Buttons/LoginBtnDown.png", ClientAPI::mainRenderer, vec2(100,600), false, 1.0f, SDL_FLIP_NONE);
	spritePressed->SetColor(255,0,0);
	spritePressed->SetTextScale(0.6f);

	//spriteHover = new Sprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteHover = new Sprite("../Assets/Images/Buttons/LoginBtnHover.png", ClientAPI::mainRenderer, vec2(100,600), false, 1.0f, SDL_FLIP_NONE);
	spriteHover->SetColor(255,0,0);
	spriteHover->SetTextScale(0.6f);

	buttonState = UNPRESSED;
	SetSprite(spriteUnpressed);
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