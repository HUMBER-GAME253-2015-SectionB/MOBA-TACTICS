//Author:	Alejandro Zielinsky, Kees Vermeulen
//Date:		3/4/2015(AZ), 3/6/2015(KV)

#pragma once
#include "GUIElement.h";
#include "Sprite.h"
#include <string>

enum ButtonState{UNPRESSED, PRESSED};

class Button : public GUIElement
{
protected:
	bool isVisible;
	Sprite *sprite, *spriteUnpressed, *spritePressed, *spriteHover;
public:
	ButtonState buttonState;
	bool isBeingHovered;
	virtual void OnClick() = 0;
	virtual void OnHover() = 0;
	virtual void Update();
	virtual void Draw();
	void Show();
	void Hide();
	bool CheckMouseCollision(int x, int y);
	void SetSprite(Sprite* sprite);

};

