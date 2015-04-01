//Author:	Mathieu Violette
//Date:		3/23/2015(MV)

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Menu.h"
#include "SplashButton.h"

class SplashScreen : public Menu
{
private:
	float delayDuration, delay;
public:
	SplashScreen();
	void Update();
};
#endif