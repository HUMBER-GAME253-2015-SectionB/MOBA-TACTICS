//Author:	Mathieu Violette , Alejandro Zielinsky
//Date:		3/10/2015(MV),     3/18/2015(MV)

#ifndef TEXTINPUT_H
#define TEXTINPUT_H
#include "GUIElement.h"
#include "TextSprite.h"
#include <string>

enum TextInputState{UNFOCUSED, FOCUSED};

class TextInput : public GUIElement
{
protected:
	bool hasFocus;
	Sprite *sprite, *spriteUnfocused, *spriteFocused;
	std::string text;
	SDL_Rect dimentions;
	void SetSprite(Sprite* sprite);
public:
	TextInput(SDL_Rect& dimentions);
	~TextInput();
	TextInputState currentState;
	void OnClick();
	void Update();
	void Draw();
	void Show();
	void Hide();
	bool CheckMouseCollision(int x, int y);
	void setFocus(bool newVal);
	void SetText(const char* _text);
	void TextAction_Backspace();
	std::string GetText() const;
	void SelectSprite();
};

#endif