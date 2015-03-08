//Author:	Alejandro Zielinsky, Mathieu Violette
//Date:		3/4/2015(AZ), 3/8/2015(MV)

#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

class GUIElement
{

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Show() = 0;
	virtual void Hide() = 0;

};

#endif