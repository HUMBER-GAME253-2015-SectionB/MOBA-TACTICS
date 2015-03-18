//Author: Alejandro Zielinsky
//Date:	  3/18/2015
#include "TextHandler.h"

TextHandler::TextHandler()
{
	registeredTextInputs = new SList<TextInput*>();
	activeTextbox = NULL;
}

void TextHandler::SubscribeTextInput(TextInput& tbox)
{
	registeredTextInputs->push_front(&tbox);
}

void TextHandler::RemoveTextInput()
{
	registeredTextInputs->pop_front();
}

void TextHandler::RemoveTextInput(TextInput& tbox)
{
	SList<TextInput*>::Iterator target = registeredTextInputs->find(&tbox);
	if(&tbox == activeTextbox)
		activeTextbox = NULL;


	registeredTextInputs->erase(target);

}

void TextHandler::RemoveAll()
{
	registeredTextInputs->clear();
}

bool TextHandler::HandleEventMouseDown(int x, int y)
{
	for(SList<TextInput*>::Iterator i = registeredTextInputs->begin(); i != registeredTextInputs->end(); ++i)
	{
		if((*i)->CheckMouseCollision(x, y))
		{
			(*i)->currentState = TIS_PRESSED;
			return true;
		}
	}
	return false;
}

bool TextHandler::HandleEventMouseUp(int x, int y)
{
	bool succeess = false;
	SList<TextInput*>::Iterator target = registeredTextInputs->begin();

	for (SList<TextInput*>::Iterator i = registeredTextInputs->begin(); i != registeredTextInputs->end(); ++i)
	{
		if ((*i)->CheckMouseCollision(x, y) && (*i)->currentState == TIS_PRESSED)
		{
			target = i;
			succeess = true;
		}

		(*i)->currentState = TIS_UNPRESSED;
	}

	if (succeess)
	{
		(*target)->OnClick();
		activeTextbox = *target;
		
	}
	else
	{
		if(activeTextbox)
		activeTextbox->setFocus(false);
		activeTextbox = NULL;
		
	}
	return succeess;
}

bool TextHandler::HandleTextInput(std::string& txt)
{
	if(activeTextbox)
	{
		activeTextbox->SetText(txt.c_str());
	}
	return true;
}


TextHandler& TextHandler::GetInstance()
{
	static TextHandler instance;
	return instance;
}