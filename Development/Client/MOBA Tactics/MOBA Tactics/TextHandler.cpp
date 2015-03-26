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
	bool succeess = false;
	SList<TextInput*>::Iterator target = registeredTextInputs->begin();

	for (SList<TextInput*>::Iterator i = registeredTextInputs->begin(); i != registeredTextInputs->end(); ++i)
	{
		if ((*i)->CheckMouseCollision(x, y))
		{
			target = i;
			succeess = true;

			if ((*i)->currentState == UNFOCUSED)
			{				
				(*i)->currentState = FOCUSED;
			}
		}
		else if ((*i)->currentState == FOCUSED)
		{
			(*i)->currentState = UNFOCUSED;
		}
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

		activeTextbox = nullptr;
		
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

bool TextHandler::HandleTextInput(SDL_Scancode& scan)
{
	if (activeTextbox)
	{
		switch (scan)
		{
			case SDL_SCANCODE_BACKSPACE:

				break;
		}
	}
	return true;
}

TextHandler& TextHandler::GetInstance()
{
	static TextHandler instance;
	return instance;
}