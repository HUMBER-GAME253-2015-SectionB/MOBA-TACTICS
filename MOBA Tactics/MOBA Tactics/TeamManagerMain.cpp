#include "TeamManager.h"
#include "Character.h"
#include <iostream>
/*
//Michael Kochen, Trey Hesketh
Last Updated 03/11
*/

int main(int argc, char** argv)
{
	TeamManager TM;
	TM.CreateTeamWithPlayers();
	TM.ChracterList();
	TM.TeamList();
	TM.DeleteCharacter();
	TM.ChracterList();
	
	system("PAUSE");
}