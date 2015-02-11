//Author:	Mathieu Violette
//Date:		3/22/2014(MV)

#include "GameManager.h"

int main(int argc, char *argv[])
{
	GameManager *newGame = new GameManager();
	newGame->StartProgram();
	
	delete newGame;

	return 0;
}