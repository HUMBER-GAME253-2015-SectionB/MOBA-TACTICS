//Author	Mathieu Violette
//Date		3102015(MV)

#ifndef __SERVERBUTTON_H_INCLUDED__
#define __SERVERBUTTON_H_INCLUDED__

#include "Button.h"

class ServerButton : public Button
{
public:
	bool selected;
	ServerButton();
	ServerButton(std::string text, int x, int y);

	void OnClick() override;
	void OnHover() override;
	void Update() override;
	void Draw() override;

};

#endif