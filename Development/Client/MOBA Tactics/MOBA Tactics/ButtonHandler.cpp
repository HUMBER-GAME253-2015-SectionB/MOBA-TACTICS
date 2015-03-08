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

bool ButtonHandler::HandleEvent(Button* btn)
{
	if(btn->buttonState == PRESSED)
	{
		btn->OnClick();
		return true;
	}
	else
		return false;
}
bool ButtonHandler::HandleEvents()
{
	for(SList<Button*>::Iterator i = registeredBtns->begin(); i != registeredBtns->end(); ++i)
	{
		if(HandleEvent(*i))
			return true;
	}
	return false;
}

ButtonHandler& ButtonHandler::GetInstance()
{
	static ButtonHandler instance;
	return instance;
}