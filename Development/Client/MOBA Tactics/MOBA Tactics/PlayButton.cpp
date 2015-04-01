//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#include "PlayButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

PlayButton::PlayButton()
	: Button()
{
	//spriteUnpressed = new Sprite(ClientAPI::Color.Purple, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteUnpressed = new Sprite("../Assets/Images/Buttons/PlayBtnUp.png", ClientAPI::mainRenderer, vec2(100,500), false, 1.0f, SDL_FLIP_NONE);
	spriteUnpressed->SetColor(255,0,0);

	//spritePressed = new Sprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spritePressed = new Sprite("../Assets/Images/Buttons/PlayBtnDown.png", ClientAPI::mainRenderer, vec2(100,500), false, 1.0f, SDL_FLIP_NONE);
	spritePressed->SetColor(255,0,0);

	//spriteHover = new Sprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteHover = new Sprite("../Assets/Images/Buttons/PlayBtnHover.png", ClientAPI::mainRenderer, vec2(100,500), false, 1.0f, SDL_FLIP_NONE);
	spriteHover->SetColor(255,0,0);
}

void PlayButton::OnClick()
{
	Game::gameStateManager.QueueChangeToGameState(GameState::SCENE);
}

void PlayButton::OnHover()
{

}

