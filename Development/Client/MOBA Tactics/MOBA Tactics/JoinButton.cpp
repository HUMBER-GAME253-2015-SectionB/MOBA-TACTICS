#include "JoinButton.h"
#include "LobbyList.h"
#include "ServerButton.h"
	JoinButton::JoinButton()
		: Button()
	{
		//spriteUnpressed = new TextSprite(ClientAPI::Color.Purple, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
		spriteUnpressed = new Sprite("../Assets/Images/Buttons/LoginBtnUp.png", ClientAPI::mainRenderer, vec2(100, 600), false, 1.0f, SDL_FLIP_NONE);
		spriteUnpressed->SetColor(255, 0, 0);

		//spritePressed = new TextSprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
		spritePressed = new Sprite("../Assets/Images/Buttons/LoginBtnDown.png", ClientAPI::mainRenderer, vec2(100, 600), false, 1.0f, SDL_FLIP_NONE);
		spritePressed->SetColor(255, 0, 0);
		//spritePressed->SetTextScale(0.6f);

		//spriteHover = new TextSprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, ClientAPI::createRectangle(300, 200, 424, 150));
		spriteHover = new Sprite("../Assets/Images/Buttons/LoginBtnHover.png", ClientAPI::mainRenderer, vec2(100, 600), false, 1.0f, SDL_FLIP_NONE);
		spriteHover->SetColor(255, 0, 0);
		//spriteHover->SetTextScale(0.6f);

		buttonState = UNPRESSED;
		SetSprite(spriteUnpressed);
	}

	void JoinButton::OnClick()
	{
		LobbyList::GetSelection().LoadScene();
	}

	void JoinButton::OnHover()
	{

	}
