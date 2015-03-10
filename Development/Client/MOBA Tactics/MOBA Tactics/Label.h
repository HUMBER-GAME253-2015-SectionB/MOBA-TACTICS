//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#ifndef LABEL_H
#define LABEL_H

#include "GUIElement.h";
#include "Sprite.h"
#include <string>

class Label : public GUIElement
{
protected:
	Sprite *sprite;
	std::string text;
	SDL_Rect dimentions;
public:
	Label(std::string _text, SDL_Rect& dimentions);
	~Label();
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