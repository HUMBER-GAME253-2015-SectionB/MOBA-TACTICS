//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "GUIElement.h";
#include "Sprite.h"
#include <string>

class TextInput : public GUIElement
{
protected:
	Sprite *sprite;
	std::string text;
	SDL_Rect dimentions;
public:
	TextInput(SDL_Rect& dimentions);
	~TextInput();
	
	bool hasFocus;

	void OnClick();
	void OnHover();
	void Update();
	void Draw();
	void Show();
	void Hide();
	bool CheckMouseCollision(int x, int y);

	void SetText(char* _text);
	char* GetText() const;
};

#endif