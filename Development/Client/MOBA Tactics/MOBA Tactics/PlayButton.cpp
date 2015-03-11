//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#include "PlayButton.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

PlayButton::PlayButton()
	: Button()
{
	spriteUnpressed = new Sprite(ClientAPI::Color.Purple, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteUnpressed->SetText("Play");
	spriteUnpressed->SetTextScale(0.6f);

	spritePressed = new Sprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spritePressed->SetText("Play");
	spritePressed->SetTextScale(0.6f);

	spriteHover = new Sprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
	spriteHover->SetText("Play");
	spriteHover->SetTextScale(0.6f);
}

void PlayButton::OnClick()
{
	Game::gameStateManager.QueueChangeToGameState(GameState::SCENE);
}

void PlayButton::OnHover()
{

}
