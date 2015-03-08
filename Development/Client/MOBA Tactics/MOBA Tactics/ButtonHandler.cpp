#include "ButtonHandler.h"

ButtonHandler::ButtonHandler()
{
	registeredBtns = new SList<Button>();
}

void ButtonHandler::SubscribeButton(Button btn)
{
	registeredBtns->push_front(btn);
}

void ButtonHandler::RemoveButton(int index)
{
	registeredBtns->pop_at(index);
}

void ButtonHandler::RemoveAll()
{
	registeredBtns->clear();
}

bool ButtonHandler::HandleEvent(Button btn)
{
	if(btn.btnState == PRESSED)
	{
		btn.onClick();
		return true;
	}
	else
		return false;
}
bool ButtonHandler::HandleEvents()
{
	for(SList<Button>::Iterator i = registeredBtns->begin(); i != registeredBtns->end(); ++i)
	{
		if(HandleEvent(*i))
			return true;
	}
	return false;
}
ButtonHandler ButtonHandler::GetInstance()
{
	return ButtonHandler();
}