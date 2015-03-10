//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#include "MainMenu.h"
#include "LogoutButton.h"
#include "PlayButton.h"

MainMenu::MainMenu()
{
	buttons.push_front(new LogoutButton());
	buttons.push_front(new PlayButton());
}

