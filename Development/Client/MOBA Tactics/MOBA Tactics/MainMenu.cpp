//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#include "MainMenu.h"
#include "LogoutButton.h"
#include "PlayButton.h"

MainMenu::MainMenu()
{
	//labels.push_front(new Label("Main Menu", ClientAPI::createRectangle(200, 50, 674, 100)));

	buttons.push_front(new LogoutButton());
	buttons.push_front(new PlayButton());
	title = new Sprite("../Assets/Images/TitleLogo.png", ClientAPI::mainRenderer, vec2(100,20), false, 1.0f, SDL_FLIP_NONE);
	background = new Sprite("../Assets/Images/Background.png", ClientAPI::mainRenderer, vec2(0,170), false, 1.0f, SDL_FLIP_NONE);
}

