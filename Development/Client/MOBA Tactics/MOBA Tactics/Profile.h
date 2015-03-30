//Author:	Mathieu Violette
//Date:		3/30/2015(MV)

#ifndef _PROFILE_H_
#define _PROFILE_H_

#include <string>
#include "Character.h"
#include "SList.h"

using namespace std;

class Profile
{
private:
	string userName;
	SList<Character*> characters;
	//SList<Team*> teams;

public:
	Profile(string _userName, SList<Character*> _characters);
	~Profile();

	string GetName() const;
};

#endif