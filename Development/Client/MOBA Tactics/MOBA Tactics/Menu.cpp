//Author:	Mathieu Violette
//Date:		3/5/2015(MV), 3/8/2015(MV)

#include "Menu.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

Menu::Menu()
{
	//Populate List of Buttons in constructor.
}

Menu::~Menu()
{
	Unload();
}

void Menu::Load()
{
	//Register Menu
	Game::eventManager.RegisterMenu(*this);
}

void Menu::Unload()
{
	//Unregister menu
	Game::eventManager.UnregisterMenu(*this);
	
	//Remove buttons from SList
	buttons.clear();
}

void Menu::Update()
{
	//Call Update Of Each Button
	for (SList<Button*>::Iterator i = buttons.begin(); i != buttons.end(); i++)
	{
		(*i)->Update();
	}

}

void Menu::Draw(SDL_Renderer* ren) const
{
	SList<Button*>::Iterator i = buttons.begin();
	for (; i != buttons.end(); i++)
	{
		(*i)->Draw();
	}
}

const SList<Button*>& Menu::GetButtons() const
{
	return buttons;
}
