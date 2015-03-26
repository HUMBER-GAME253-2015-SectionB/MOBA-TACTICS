//Author:	Alejandro Zielinsky, Kees Vermeulen
//Date:		3/4/2015(AZ), 3/6/2015(KV)

#pragma once
#include "GUIElement.h"
#include "TextSprite.h"
#include <string>

enum ButtonState{UNPRESSED, PRESSED, HOVER};

class Button : public GUIElement
{
private:
protected:
	Sprite *sprite, *spriteUnpressed, *spritePressed, *spriteHover;
	void SetSprite(Sprite* sprite);
public:
	Button();
	~Button();

	ButtonState buttonState;
	bool isBeingHovered;
	virtual void OnClick() = 0;
	virtual void OnHover() = 0;
	virtual void Update();
	virtual void Draw();
	void Show();
	void Hide();
	void SelectSprite();
	bool CheckMouseCollision(int x, int y);
};

