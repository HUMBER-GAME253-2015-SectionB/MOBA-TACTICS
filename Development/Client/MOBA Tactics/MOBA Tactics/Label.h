//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#ifndef LABEL_H
#define LABEL_H
#include "GUIElement.h"
#include "TextSprite.h"
#include <string>

class Label : public GUIElement
{
protected:
	Sprite *sprite;
	std::string text;
	SDL_Rect dimentions;
	TTF_Font* font;
	SDL_Color textColor;
public:	
	//Enter -1 into dimentions' x or y to center on that axis.
	Label(const char* _text, SDL_Rect& dimentions, TTF_Font* _font);
	~Label();
	void OnClick();
	void OnHover();
	void Update();
	void Draw();
	void Show();
	void Hide();
	bool CheckMouseCollision(int x, int y);

	void SetTextColor(SDL_Color color);

	void SetText(char* _text);
	std::string GetText() const;
};

#endif