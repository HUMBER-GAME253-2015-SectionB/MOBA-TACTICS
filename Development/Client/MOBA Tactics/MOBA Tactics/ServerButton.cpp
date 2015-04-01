//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#include "ServerButton.h"
#include "LobbyList.h"

//To use static members of game class. MUST BE IN CPP FILE.
#include "Game.h"

ServerButton::ServerButton(std::string text, int x, int y)
: Button()
{
	spriteUnpressed = new TextSprite(ClientAPI::Color.Purple, ClientAPI::mainRenderer, ClientAPI::createRectangle(x, y, 848, 35), ClientAPI::Font.Droid_Bold_20);
	((TextSprite*)spriteUnpressed)->SetText(text.c_str());
	spritePressed = new TextSprite(ClientAPI::Color.Blue, ClientAPI::mainRenderer, ClientAPI::createRectangle(x, y, 848, 35), ClientAPI::Font.Droid_Bold_20);
	((TextSprite*)spritePressed)->SetText(text.c_str());
	spriteHover = new TextSprite(ClientAPI::Color.Green, ClientAPI::mainRenderer, ClientAPI::createRectangle(x, y, 848, 35), ClientAPI::Font.Droid_Bold_20);
	((TextSprite*)spriteHover)->SetText(text.c_str());
}

void ServerButton::OnClick()
{
	LobbyList::SetSelection(this);
}

void ServerButton::OnHover()
{

}

void ServerButton::Update()
{
	if (!selected)
		SelectSprite();
	else
		SetSprite(spritePressed);
}

void ServerButton::Draw()
{
	if (isVisible)
	{
		if (!selected)
		{
			SelectSprite();
			sprite->Draw(ClientAPI::mainRenderer);
		}
		else
		{
			SetSprite(spritePressed);
			sprite->Draw(ClientAPI::mainRenderer);
		}
	}
}