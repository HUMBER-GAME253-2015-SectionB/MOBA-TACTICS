//Author:	Mathieu Violette, Alejandro Zielinsky
//Date:		3/8/2015(MV), 3/18/2015(AZ)

#include "EventManager.h"
#include "Game.h"

ButtonHandler EventManager::buttonHandler = ButtonHandler::GetInstance();
SceneHandler EventManager::sceneHandler = SceneHandler::GetInstance();
TextHandler EventManager::textHandler = TextHandler::GetInstance();

class TextInput;

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
		if (Game::gameStateManager.GetGameState() == GameState::SCENE)
			sceneHandler.HandleEventMouseDown(MouseX, MouseY);
		else
		{
			buttonHandler.HandleEventMouseDown(MouseX, MouseY);
			textHandler.HandleEventMouseDown(MouseX,MouseY);
		}
	}

	//Check for left button up
	if (event->button.type == SDL_MOUSEBUTTONUP &&
		event->button.button == SDL_BUTTON_LEFT &&
		SDL_BUTTON(PreviousMouseState) != SDL_BUTTON(MouseState))
	{
		if (Game::gameStateManager.GetGameState() == GameState::SCENE)
			sceneHandler.HandleEventMouseUp(MouseX, MouseY);
		else
		{
			buttonHandler.HandleEventMouseUp(MouseX, MouseY);
		}
	}

	//Check for mouse movement
	if (PreviousMouseX != MouseX ||
		PreviousMouseY != MouseY)
	{
		UpdateHoverState();
	}

	if (event->type == SDL_KEYDOWN)
	{
		if (Game::gameStateManager.GetGameState() == GameState::SCENE)
		{
			sceneHandler.HandleEventKeyDown(event->key.keysym.sym);
		}
		else
		{
			textHandler.HandleTextInput(event->key.keysym.scancode);			
		}
	}
	
	if (event->type == SDL_KEYUP)
	{
		if (Game::gameStateManager.GetGameState() == GameState::SCENE)
		{
			sceneHandler.HandleEventKeyUp(event->key.keysym.sym);
		}
	}

	if(event->type == SDL_TEXTINPUT)
	{
		if(Game::gameStateManager.GetGameState() != GameState::SCENE)
		{
			textHandler.HandleTextInput(std::string(event->text.text));
		}
	}
	
	if (event->type == SDL_MOUSEWHEEL)
	{
		sceneHandler.HandleEventMouseWheel(event->wheel);
		
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
	if (Game::gameStateManager.GetGameState() == GameState::SCENE)
		sceneHandler.HandleEventMouseHover(MouseX, MouseY);
	else
		buttonHandler.HandleEventMouseHover(MouseX, MouseY);
}

void EventManager::RegisterMenu(const Menu& menu)
{
	//Register buttons to button handler
	for (SList<Button*>::Iterator i = menu.GetButtons().begin(); i != menu.GetButtons().end(); i++)
	{
		buttonHandler.SubscribeButton(*(*i));
	}

	//Register TextInputs to TextInput handler
	for (SList<TextInput*>::Iterator i = menu.GetTextInputs().begin(); i != menu.GetTextInputs().end(); i++)
	{
		textHandler.SubscribeTextInput(*(*i));
	}
}

void EventManager::UnregisterMenu(const Menu& menu)
{
	//Unregister buttons to button handler
	for (SList<Button*>::Iterator i = menu.GetButtons().begin(); i != menu.GetButtons().end(); i++)
	{
		buttonHandler.RemoveButton(*(*i));
	}

	//Unregister TextInputs to TextInput handler
	for (SList<TextInput*>::Iterator i = menu.GetTextInputs().begin(); i != menu.GetTextInputs().end(); i++)
	{
		textHandler.RemoveTextInput(*(*i));
	}
}

SceneHandler* EventManager::GetSceneHandler()
{
	return &sceneHandler;
}