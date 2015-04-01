//Author:	David Vo, Mathieu Violette, Kees Vermeulen
//Date:		2/23/2014(DV), 3/5/2015(MV), 2/25/2015(KV)

#ifndef __LOBBYLIST_H_INCLUDED__
#define __LOBBYLIST_H_INCLUDED__

#include "Menu.h"

#ifndef __SERVERBUTTON_H_INCLUDED__
class ServerButton;
#endif

class LobbyList : public Menu
{
public:
	LobbyList();
	~LobbyList();

	void Update();

	void AddServer(std::string text);
	void RemoveServer(size_t index);
	static void SetSelection(ServerButton *btn);

private:
	static SList<ServerButton*> servers;

};

#endif