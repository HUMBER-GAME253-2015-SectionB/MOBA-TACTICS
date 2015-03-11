//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#include "LoginScreen.h"
#include "LoginButton.h"

LoginScreen::LoginScreen()
{
	buttons.push_front(new LoginButton());
	title = new Sprite("../Assets/Images/TitleLogo.png", ClientAPI::mainRenderer, vec2(100,20), false, 1.0f, SDL_FLIP_NONE);
	background = new Sprite("../Assets/Images/Background.png", ClientAPI::mainRenderer, vec2(0,170), false, 1.0f, SDL_FLIP_NONE);
}

LoginScreen::~LoginScreen()
{

}


