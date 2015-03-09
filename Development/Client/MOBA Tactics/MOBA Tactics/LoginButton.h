//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#ifndef __LOGINBUTTON_H_INCLUDED__
#define __LOGINBUTTON_H_INCLUDED__

#include "Button.h"

class LoginButton : public Button
{

public:
	LoginButton();
	~LoginButton();

	void OnClick();
	void OnHover();
};

#endif