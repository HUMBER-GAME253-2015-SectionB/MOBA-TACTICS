//Author:	Mathieu Violette, Kees Vermeulen
//Date:		3/5/2015(MV), 3/25/2015(KV)

#include "LobbyList.h"
#include "ServerButton.h"

SList<ServerButton*> LobbyList::servers = SList<ServerButton*>();
LobbyList::LobbyList()
{
	background = new Sprite("../Assets/Images/Background.png", ClientAPI::mainRenderer, vec2(0, 170), false, 1.0f, SDL_FLIP_NONE);
	AddServer("Server1");
	AddServer("Server2");
	AddServer("Server3");
	AddServer("Server4");
	AddServer("Server5");
	AddServer("Server6");
	AddServer("Server7");
	AddServer("Server8");

}

LobbyList::~LobbyList()
{
	servers.clear();
}


void LobbyList::Update()
{
}

void LobbyList::AddServer(std::string text)
{
	servers.push_front(new ServerButton(text, 100, 100 + (40 * servers.size())));
	buttons.push_front(servers.front());
}

void LobbyList::RemoveServer(size_t index)
{
	servers.pop_at(index);
}

void LobbyList::SetSelection(ServerButton *btn)
{
	if (btn != nullptr)
	{
		SList<ServerButton*>::Iterator cur = servers.begin();
		for (; cur != servers.end(); cur++)
		{
			(*cur)->selected = false;
		}
		btn->selected = true;
	}
}