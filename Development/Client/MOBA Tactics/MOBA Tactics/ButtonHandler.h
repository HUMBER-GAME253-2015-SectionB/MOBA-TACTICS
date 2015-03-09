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
public:
	static ButtonHandler& GetInstance();
	bool HandleEventMouseDown(int x, int y);
	bool HandleEventMouseUp(int x, int y);
	bool HandleEventMouseHover(int x, int y);
	void SubscribeButton(Button& btn);
	void RemoveButton();
	void RemoveButton(Button& btn);
	void RemoveAll();
};