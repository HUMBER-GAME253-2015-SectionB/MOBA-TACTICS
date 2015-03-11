//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#include "LoginScreen.h"
#include "LoginButton.h"

LoginScreen::LoginScreen()
{
	labels.push_front(new Label("MOBA Tactics", ClientAPI::createRectangle(200, 50, 674, 100)));
	buttons.push_front(new LoginButton());
}


