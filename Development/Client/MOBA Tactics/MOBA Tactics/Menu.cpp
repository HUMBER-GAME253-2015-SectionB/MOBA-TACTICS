//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#include "Menu.h"

IGame* Menu::gameObject = nullptr;

Menu::Menu()
{
	
}

Menu::~Menu()
{
	Unload();
}

void Menu::InitMenus(IGame* _game)
{
	if (gameObject == nullptr)
		gameObject = _game;
}

void Menu::Load()
{
	
}

void Menu::Unload()
{
	//Unregister buttons
	


	//Remove buttons from SList
	buttons.clear();
}

void Menu::Update()
{

}

void Menu::Draw(SDL_Renderer* ren) const
{
	SList<Button>::Iterator i = buttons.begin();

	for (; i != buttons.end(); i++)
	{
		// *i.Draw();
	}
}

const SList<Button> Menu::GetButtons() const
{
	return buttons;
}
