//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#include "MainMenu.h"
#include "LogoutButton.h"

MainMenu::MainMenu()
{
	buttons.push_front(new LogoutButton());
}

MainMenu::~MainMenu()
{

}


