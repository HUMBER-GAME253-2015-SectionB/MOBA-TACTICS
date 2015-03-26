//Author: Alejandro Zielinsky
//Date: 3/18/2015(AZ)

#pragma once
#include "SList.h"
#include "TextInput.h"
class TextHandler
{
public:
	//~TextHandler(void);

	static TextHandler& GetInstance();
	bool HandleTextInput(std::string&);
	bool HandleTextInput(SDL_Scancode&);
	bool HandleEventMouseDown(int x, int y);
	void SubscribeTextInput(TextInput& tbox);
	void RemoveTextInput();
	void RemoveTextInput(TextInput& tbox);
	void RemoveAll();
	

private:
	TextHandler(void);
	SList<TextInput*> *registeredTextInputs;
	TextInput* activeTextbox;
	
	
};

