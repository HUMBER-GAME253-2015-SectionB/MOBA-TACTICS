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

	//Check for left button down
	if (event->button.type == SDL_MOUSEBUTTONDOWN && 
		event->button.button == SDL_BUTTON_LEFT &&
		SDL_BUTTON(PreviousMouseState) != SDL_BUTTON(MouseState))
	{
		buttonHandler.HandleEventMouseDown(MouseX, MouseY);
	}

	//Check for left button up
	if (event->button.type == SDL_MOUSEBUTTONUP &&
		event->button.button == SDL_BUTTON_LEFT &&
		SDL_BUTTON(PreviousMouseState) != SDL_BUTTON(MouseState))
	{
		buttonHandler.HandleEventMouseUp(MouseX, MouseY);
	}

	//Check for mouse movement
	if (PreviousMouseX != MouseX ||
		PreviousMouseY != MouseY)
	{
		UpdateHoverState();
	}
	

	//Post-update: set previous mouse state
	{
		PreviousMouseState = MouseState;
		PreviousMouseX = MouseX;
		PreviousMouseY = MouseY;
	}
}

void EventManager::UpdateHoverState()
{
	buttonHandler.HandleEventMouseHover(MouseX, MouseY);
}

void EventManager::RegisterMenu(const Menu& menu)
{
	//Register buttons to button handler

	for (SList<Button*>::Iterator i = menu.GetButtons().begin(); i != menu.GetButtons().end(); i++)
	{
		buttonHandler.SubscribeButton(*(*i));
	}
}

void EventManager::UnregisterMenu(const Menu& menu)
{
	//Unregister buttons to button handler

	for (SList<Button*>::Iterator i = menu.GetButtons().begin(); i != menu.GetButtons().end(); i++)
	{
		buttonHandler.RemoveButton(*(*i));
	}
}