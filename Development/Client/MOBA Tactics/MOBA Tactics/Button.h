//Author:	Alejandro Zielinsky, Kees Vermeulen
//Date:		3/4/2015(AZ), 3/6/2015(KV)

#pragma once
#include "GUIElement.h";
#include "Sprite.h"
#include <string>

enum ButtonState{UNPRESSED, PRESSED, HOVER};

class Button : public GUIElement
{
private:
	bool isVisible;
	Sprite *image;
public:

	ButtonState buttonState;
	virtual void OnClick() = 0;
	void Show();
	void Hide();

};

