//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#ifndef __SPLASHBUTTON_H_INCLUDED__
#define __SPLASHBUTTON_H_INCLUDED__

#include "Button.h"

class SplashButton : public Button
{

public:
	SplashButton();

	void OnClick();
	void OnHover();
};

#endif