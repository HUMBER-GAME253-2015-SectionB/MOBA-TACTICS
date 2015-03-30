//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#include "MainMenu.h"
#include "LogoutButton.h"
#include "PlayButton.h"

#include "Game.h"

MainMenu::MainMenu()
{
	Label* label;
	labels.push_front(label = new Label("Main Menu", ClientAPI::createRectangle(-1, 50, 674, 100), ClientAPI::Font.Ostrich_Bold_100));
	label->SetTextColor(ClientAPI::Color.Light_Grey);

	string welcomeMessage = "Welcome, " + Game::userProfile->GetName();
	labels.push_front(label = new Label(welcomeMessage.c_str(), ClientAPI::createRectangle(700, 150, 674, 100), ClientAPI::Font.Ostrich_Bold_36));
	label->SetTextColor(ClientAPI::Color.Green);

	buttons.push_front(new LogoutButton());
	buttons.push_front(new PlayButton());

	title = new Sprite("../Assets/Images/TitleLogo.png", ClientAPI::mainRenderer, vec2(100,20), false, 1.0f, SDL_FLIP_NONE);
	background = new Sprite("../Assets/Images/Background.png", ClientAPI::mainRenderer, vec2(0,170), false, 1.0f, SDL_FLIP_NONE);
}

