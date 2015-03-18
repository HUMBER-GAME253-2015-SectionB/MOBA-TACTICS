//Author:	Mathieu Violette, Alejandro Zielinsky
//Date:		3/8/2015(MV), 3/18/2015(AZ)

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SDL.h>
#include "ButtonHandler.h"
#include "SceneHandler.h"
#include "Menu.h"
#include "TextHandler.h"

class EventManager
{
private:
	EventManager();
	static ButtonHandler buttonHandler;
	static SceneHandler sceneHandler; 
	static TextHandler textHandler;
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
	void UpdateHoverState();

	void RegisterMenu(const Menu& menu);
	void UnregisterMenu(const Menu& menu);

	SceneHandler* GetSceneHandler();
};

#endif