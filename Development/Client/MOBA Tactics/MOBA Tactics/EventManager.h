//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SDL.h>
#include "ButtonHandler.h"
#include "Menu.h"

class EventManager
{
private:
	EventManager();
	static ButtonHandler buttonHandler;
public:
	const Uint8 *KeyState;
	int MouseX, MouseY;
	Uint32 MouseState;
	int PreviousMouseX, PreviousMouseY;
	Uint32 PreviousMouseState;
	
	bool test;

	static EventManager& GetInstance();
	~EventManager();
	
	void ManageEvents(SDL_Event *event);
	void RegisterMenu(const Menu& menu);
	void UnregisterMenu(const Menu& menu);
};

#endif