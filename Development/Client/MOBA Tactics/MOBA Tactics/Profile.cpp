//Author:	Mathieu Violette
//Date:		3/30/2015(MV)

#include "Profile.h"

Profile::Profile(string _userName, SList<Character*> _characters) : userName(_userName), characters(_characters){}

Profile::~Profile()
{
	characters.clear();
}

string Profile::GetName() const
{
	return userName;
}