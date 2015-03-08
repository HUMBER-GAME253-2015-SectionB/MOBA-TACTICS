//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#include "EventManager.h"

ButtonHandler EventManager::buttonHandler = ButtonHandler::GetInstance();

EventManager& EventManager::GetInstance()
{
	static EventManager instance;
	return instance;
}

EventManager::EventManager()
{
	test = false;
}

EventManager::~EventManager()
{
	
}

void EventManager::ManageEvents(SDL_Event *event)
{
	//Pre-update: Get mouse state
	MouseState = SDL_GetMouseState(&MouseX, &MouseY); 

	//Check for button click
	if (event->button.type == SDL_MOUSEBUTTONDOWN && PreviousMouseState != MouseState)
		buttonHandler.HandleEvents();
}

void EventManager::RegisterMenu(const Menu& menu)
{
	//Register buttons to button handler
	size_t numberOfButtons = menu.GetButtons().size();

	for (SList<Button*>::Iterator i = menu.GetButtons().begin(); i != menu.GetButtons().end(); i++)
	{
		buttonHandler.SubscribeButton(*(*i));
	}
}

void EventManager::UnregisterMenu(const Menu& menu)
{
	//Unregister buttons to button handler
	size_t numberOfButtons = menu.GetButtons().size();

	for (SList<Button*>::Iterator i = menu.GetButtons().begin(); i != menu.GetButtons().end(); i++)
	{
		buttonHandler.RemoveButton(*(*i));
	}
}