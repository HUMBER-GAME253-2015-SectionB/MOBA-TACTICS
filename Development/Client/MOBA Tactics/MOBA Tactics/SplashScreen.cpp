//Author:	Mathieu Violette
//Date:		3/23/2015(MV)

#include "SplashScreen.h"
#include "Game.h"

SplashScreen::SplashScreen()
{
	delayDuration = 4;
	delay = 0;

	//buttons.push_front(new LoginButton());
	title = new Sprite("../Assets/Images/TitleLogo.png", ClientAPI::mainRenderer, vec2(100, 20), false, 1.0f, SDL_FLIP_NONE);
	background = new Sprite("../Assets/Images/Background.png", ClientAPI::mainRenderer, vec2(0, 170), false, 1.0f, SDL_FLIP_NONE);
}

void SplashScreen::Update()
{
	Menu::Update();

	delay += ClientAPI::elaspedTime / 1000.f;

	if (delay >= delayDuration)
		Game::gameStateManager.QueueChangeToGameState(GameState::LOGIN);
}
