//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "LoginButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

LoginButton::LoginButton()
	: Button()
{
	//spriteUnpressed = new TextSprite(ClientAPI::Color.Purple, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteUnpressed = new Sprite("../Assets/Images/Buttons/LoginBtnUp.png", ClientAPI::mainRenderer, vec2(100,600), false, 1.0f, SDL_FLIP_NONE);
	spriteUnpressed->SetColor(255,0,0);

	//spritePressed = new TextSprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spritePressed = new Sprite("../Assets/Images/Buttons/LoginBtnDown.png", ClientAPI::mainRenderer, vec2(100,600), false, 1.0f, SDL_FLIP_NONE);
	spritePressed->SetColor(255,0,0);
	//spritePressed->SetTextScale(0.6f);

	//spriteHover = new TextSprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteHover = new Sprite("../Assets/Images/Buttons/LoginBtnHover.png", ClientAPI::mainRenderer, vec2(100,600), false, 1.0f, SDL_FLIP_NONE);
	spriteHover->SetColor(255,0,0);
	//spriteHover->SetTextScale(0.6f);

	buttonState = UNPRESSED;
	SetSprite(spriteUnpressed);
}


void LoginButton::OnClick()
{
	
	Game::userProfile = ClientAPI::Login(LoginScreen::userName->GetText(), LoginScreen::passWord->GetText());

	if (Game::userProfile != nullptr)
		Game::gameStateManager.QueueChangeToGameState(GameState::MAINMENU);
	else
	{
		if (((Menu*)Game::gameStateManager.GetCurrentMenu())->ErrorLabel == nullptr)
			((Menu*)Game::gameStateManager.GetCurrentMenu())->ErrorLabel = new Label("Wrong Username/Password.", ClientAPI::createRectangle(-1, 550, -1, 50), ClientAPI::Font.Ostrich_Bold_36);
		else
			((Menu*)Game::gameStateManager.GetCurrentMenu())->ErrorLabel->SetText("Wrong Username/Password.");
		((Menu*)Game::gameStateManager.GetCurrentMenu())->ErrorLabel->SetTextColor(ClientAPI::Color.Red);
	}
	
}

void LoginButton::OnHover()
{

}