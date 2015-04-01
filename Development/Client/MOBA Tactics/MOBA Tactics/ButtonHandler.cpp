//Author:	Kees Vermeulen, Mathieu Violette
//Date:		3/6/2015(KV), 3/8/2015(MV)

#include "ButtonHandler.h"

ButtonHandler::ButtonHandler()
{
	registeredBtns = new SList<Button*>();
}

void ButtonHandler::SubscribeButton(Button& btn)
{
	registeredBtns->push_front(&btn);
}

void ButtonHandler::RemoveButton()
{
	registeredBtns->pop_front();
}

void ButtonHandler::RemoveButton(Button& btn)
{
	SList<Button*>::Iterator target = registeredBtns->find(&btn);
	
	registeredBtns->erase(target);
}

void ButtonHandler::RemoveAll()
{
	registeredBtns->clear();
}

bool ButtonHandler::HandleEventMouseDown(int x, int y)
{
	for(SList<Button*>::Iterator i = registeredBtns->begin(); i != registeredBtns->end(); ++i)
	{
		if((*i)->CheckMouseCollision(x, y))
		{
			(*i)->buttonState = PRESSED;
			return true;
		}
	}
	return false;
}

bool ButtonHandler::HandleEventMouseUp(int x, int y)
{
	bool succeess = false;
	SList<Button*>::Iterator target = registeredBtns->begin();

	for (SList<Button*>::Iterator i = registeredBtns->begin(); i != registeredBtns->end(); ++i)
	{
		if ((*i)->CheckMouseCollision(x, y) && (*i)->buttonState == PRESSED)
		{
			target = i;
			succeess = true;
		}
		
		(*i)->buttonState = UNPRESSED;
	}

	if (succeess)
		(*target)->OnClick();

	return succeess;
}

bool ButtonHandler::HandleEventMouseHover(int x, int y)
{
	bool succeess = false;

	for (SList<Button*>::Iterator i = registeredBtns->begin(); i != registeredBtns->end(); ++i)
	{
		if ((*i)->CheckMouseCollision(x, y))
		{
			(*i)->isBeingHovered = true;

			succeess = true;
		}
		else
		{
			(*i)->isBeingHovered = false;
		}
	}

	return succeess;
}

ButtonHandler& ButtonHandler::GetInstance()
{
	static ButtonHandler instance;
	return instance;
}