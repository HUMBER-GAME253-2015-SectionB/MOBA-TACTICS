//Author:	Kees Vermeulen, Mathieu Violette
//Date:		3/6/2015(KV), 3/8/2015(MV)

#pragma once

#include "SList.h"
#include "Button.h"

class ButtonHandler
{
private:
	ButtonHandler();
	SList<Button*> *registeredBtns;
	bool HandleEvent(Button* btn);
public:
	static ButtonHandler& GetInstance();
	bool HandleEvents();
	void SubscribeButton(Button& btn);
	void RemoveButton();
	void RemoveButton(Button& btn);
	void RemoveAll();
};