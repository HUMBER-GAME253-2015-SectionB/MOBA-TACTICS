//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#include "LoginScreen.h"
#include "LoginButton.h"

LoginScreen::LoginScreen()
{
	buttons.push_front(new LoginButton());
}

LoginScreen::~LoginScreen()
{

}


