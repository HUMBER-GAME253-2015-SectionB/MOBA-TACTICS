#pragma once

#include "SList.h"
#include "Button.h"

class ButtonHandler
{
private:
	ButtonHandler();
	SList<Button> *registeredBtns;
	bool HandleEvent(Button btn);
public:
	ButtonHandler GetInstance();
	bool HandleEvents();
	void SubscribeButton(Button btn);
	void RemoveButton(int index);
	void RemoveAll();
};