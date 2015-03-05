//Author:	Mathieu Violette
//Date:		3/5/2015(MV)

#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "IMenu.h"
#include "SList.h"

class Menu : public IMenu
{
private:
	SList<int /* Button */> buttons;
	static IGame* gameObject;
public:
	Menu();
	~Menu();

	static void InitMenus(IGame* _game);

	void Load();
	void Unload();
	virtual void Update();
	void Draw(SDL_Renderer* ren);

	void AddButton(/* Button _button */);
	void RemoveButton(int buttonIndex);
};

#endif