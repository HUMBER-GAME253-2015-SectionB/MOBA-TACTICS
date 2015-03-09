//Author:	Mathieu Violette
//Date:		3/8/2015(MV)

#ifndef __LOGOUTBUTTON_H_INCLUDED__
#define __LOGOUTBUTTON_H_INCLUDED__

#include "Button.h"

class LogoutButton : public Button
{

public:
	LogoutButton();
	~LogoutButton();

	void OnClick();
	void OnHover();
};

#endif