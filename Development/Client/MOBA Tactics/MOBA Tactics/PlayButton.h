//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#ifndef __PLAYBUTTON_H_INCLUDED__
#define __PLAYBUTTON_H_INCLUDED__

#include "Button.h"

class PlayButton : public Button
{

public:
	PlayButton();
	~PlayButton();

	void OnClick();
	void OnHover();
};

#endif