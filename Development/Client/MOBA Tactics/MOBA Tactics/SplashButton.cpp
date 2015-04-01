//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#include "SplashButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

SplashButton::SplashButton()
: Button()
{
	spriteUnpressed = new Sprite(ClientAPI::createColor(0, 0, 0, 0), ClientAPI::mainRenderer, ClientAPI::createRectangle(0, 0, 1920, 1080));
	SDL_DestroyTexture(spriteUnpressed->Image);
	spriteUnpressed->Image = nullptr;

	spritePressed = new Sprite(ClientAPI::createColor(0, 0, 0, 0), ClientAPI::mainRenderer, ClientAPI::createRectangle(0, 0, 1920, 1080));
	SDL_DestroyTexture(spritePressed->Image);
	spritePressed->Image = nullptr;

	spriteHover = new Sprite(ClientAPI::createColor(0, 0, 0, 0), ClientAPI::mainRenderer, ClientAPI::createRectangle(0, 0, 1920, 1080));
	SDL_DestroyTexture(spriteHover->Image);
	spriteHover->Image = nullptr;
}

void SplashButton::OnClick()
{
	Game::gameStateManager.QueueChangeToGameState(GameState::LOGIN);
}

void SplashButton::OnHover()
{

}
