//Author:	Mathieu Violette, Kees Vermeulen
//Date:		3/5/2015(MV), 3/10/2015

#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "IMenu.h"
#include "Button.h"
#include "Label.h"
#include "TextInput.h"
#include "SList.h"

class Menu : public IMenu
{
protected:
	SList<Button*> buttons;
	Sprite *background;
	Sprite *title;
	SList<Label*> labels;
	SList<TextInput*> textInputs;
public:
	Menu();
	~Menu();
	
	void Load();
	void Unload();
	virtual void Update();
	void Draw(SDL_Renderer* ren) const;
	
	const SList<Button*>& GetButtons() const;
	const SList<TextInput*>& GetTextInputs() const;

	Label* ErrorLabel;
};

#endif