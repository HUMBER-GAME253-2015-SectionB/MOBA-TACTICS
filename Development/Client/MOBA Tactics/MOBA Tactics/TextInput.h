//Author:	Mathieu Violette , Alejandro Zielinsky
//Date:		3/10/2015(MV),     3/18/2015(MV)

#ifndef TEXTINPUT_H
#define TEXTINPUT_H
#include "GUIElement.h"
#include "Sprite.h"
#include <string>

enum TextInputState{TIS_UNPRESSED,TIS_PRESSED};
class TextInput : public GUIElement
{
protected:
	bool hasFocus;
	Sprite *sprite;
	std::string text;
	SDL_Rect dimentions;
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
	std::string GetText() const;
};

#endif