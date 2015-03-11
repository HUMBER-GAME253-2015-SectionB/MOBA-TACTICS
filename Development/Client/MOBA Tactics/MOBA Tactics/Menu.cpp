//Author:	Mathieu Violette Kees Vermeulen
//Date:		3/5/2015(MV), 3/8/2015(MV), 3/10/2015

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

	//Init Buttons
	for (SList<Button*>::Iterator i = buttons.begin(); i != buttons.end(); i++)
	{
		(*i)->SelectSprite();
	}

	//Check button hover state
	Game::eventManager.UpdateHoverState();
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
	//Call Update Of Each Label
	for (SList<Label*>::Iterator i = labels.begin(); i != labels.end(); i++)
	{
		(*i)->Update();
	}

	//Call Update Of Each Button
	for (SList<Button*>::Iterator i = buttons.begin(); i != buttons.end(); i++)
	{
		(*i)->Update();
	}
}

void Menu::Draw(SDL_Renderer* ren) const
{
<<<<<<< HEAD
	if(background != NULL)
		background->Draw(ren);
	if(title != NULL)
		title->Draw(ren);
=======
	//Draw Labels
	for (SList<Label*>::Iterator i = labels.begin(); i != labels.end(); i++)
	{
		(*i)->Draw();
	}

	//Draw Buttons
>>>>>>> origin/Client
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
