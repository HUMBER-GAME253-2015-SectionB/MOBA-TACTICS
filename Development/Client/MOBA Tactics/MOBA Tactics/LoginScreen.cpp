//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#include "LoginScreen.h"
#include "LoginButton.h"

TextInput* LoginScreen::userName;
TextInput* LoginScreen::passWord;

LoginScreen::LoginScreen()
{
	Label* label;

	labels.push_front(new Label("Login Screen", ClientAPI::createRectangle(-1, 100, -1, -1), ClientAPI::Font.Ostrich_Bold_100));
	label = new Label("Login Screen", ClientAPI::createRectangle(-1, 95, -1, -1), ClientAPI::Font.Ostrich_Bold_100);
	label->SetTextColor(ClientAPI::Color.Light_Grey);
	labels.push_back(label);

	//Label with Shadow effect
	label = new Label("Username:", ClientAPI::createRectangle(125, 250, -1, 100), ClientAPI::Font.Ostrich_Bold_72);
	labels.push_back(label);
	label = new Label("Username:", ClientAPI::createRectangle(123, 248, -1, 100), ClientAPI::Font.Ostrich_Bold_72);
	label->SetTextColor(ClientAPI::Color.Light_Grey);
	labels.push_back(label);
	textInputs.push_front(userName = new TextInput(ClientAPI::createRectangle(400, 250, 474, 100), ClientAPI::Font.Droid_Regular_36, 14));

	//Label with Shadow effect
	label = new Label("Password:", ClientAPI::createRectangle(125, 400, -1, 100), ClientAPI::Font.Ostrich_Bold_72);
	labels.push_back(label);
	label = new Label("Password:", ClientAPI::createRectangle(123, 398, -1, 100), ClientAPI::Font.Ostrich_Bold_72);
	labels.push_back(label);
	label->SetTextColor(ClientAPI::Color.Light_Grey);
	textInputs.push_front(passWord = new TextInput(ClientAPI::createRectangle(400, 400, 474, 100), ClientAPI::Font.Droid_Regular_36, 14));

	buttons.push_front(new LoginButton());
	title = new Sprite("../Assets/Images/TitleLogo.png", ClientAPI::mainRenderer, vec2(100,20), false, 1.0f, SDL_FLIP_NONE);
	background = new Sprite("../Assets/Images/Background.png", ClientAPI::mainRenderer, vec2(0,170), false, 1.0f, SDL_FLIP_NONE);
}


