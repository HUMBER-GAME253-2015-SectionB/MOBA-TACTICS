//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "IMenu.h"
#include "Button.h"
#include "Label.h"
#include "SList.h"

class Menu : public IMenu
{
protected:
	SList<Button*> buttons;
	SList<Label*> labels;
public:
	Menu();
	~Menu();
	
	void Load();
	void Unload();
	virtual void Update();
	void Draw(SDL_Renderer* ren) const;
	
	const SList<Button*>& GetButtons() const;

};

#endif