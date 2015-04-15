#include <SDL_net.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;


int main(int argc, char**argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();


	SDLNet_Quit();
	SDL_Quit();
	return 0;
};