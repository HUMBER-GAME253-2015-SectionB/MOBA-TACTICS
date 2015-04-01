//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "LogoutButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"
#include "LoginScreen.h"

LogoutButton::LogoutButton()
	: Button()
{
	
		//spriteUnpressed = new TextSprite(ClientAPI::Color.Purple, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteUnpressed = new Sprite("../Assets/Images/Buttons/LogoutBtnUp.png", ClientAPI::mainRenderer, vec2(100,600), false, 1.0f, SDL_FLIP_NONE);
	spriteUnpressed->SetColor(255,0,0);

	//spritePressed = new TextSprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spritePressed = new Sprite("../Assets/Images/Buttons/LogoutBtnDown.png", ClientAPI::mainRenderer, vec2(100,600), false, 1.0f, SDL_FLIP_NONE);
	spritePressed->SetColor(255,0,0);

	//spriteHover = new TextSprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteHover = new Sprite("../Assets/Images/Buttons/LogoutBtnHover.png", ClientAPI::mainRenderer, vec2(100,600), false, 1.0f, SDL_FLIP_NONE);
	spriteHover->SetColor(255,0,0);
}

void LogoutButton::OnClick()
{
	Game::gameStateManager.QueueChangeToGameState(GameState::LOGIN);
}

void LogoutButton::OnHover()
{

}
