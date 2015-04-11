#include <iostream>
#include <fstream>
#include <string>
#include <list>
/*
//Marc Antione
Last Updated 03/11
*/

using namespace std;

void init();
void newLobby();
void joinLobby();
string openLobby(string name);

list<string> lobbyList;

void init()
{
	char input;
	cout << "Create or join a lobby, (c)reate new, (j)oin" << endl;
	cin >> input;

	switch (input)
	{
	case 'c':
		newLobby();
		break;
	case 'j':
		joinLobby();
		break;
	}
}

void newLobby()
{
	string lobbyName;
	cout << "Name your lobby (no spaces):" << endl;
	cin >> lobbyName;
	
	bool exist = false;
	for(list<string>::iterator name = lobbyList.begin(); name != lobbyList.end(); name++)
	{
		if (lobbyName == *name)
		{
			exist = true;
		}
	}
	
	if (exist)
		cout << "This lobby already exists." << endl;
	else
		lobbyList.push_back(lobbyName);

	init();
}
void joinLobby()
{
	if (lobbyList.empty())
	{
		cout << "No lobby created." << endl;
		init();
	}
	cout << "Lobbies:" << endl;
	for (list<string>::iterator name = lobbyList.begin(); name != lobbyList.end(); name++)
	{
		cout << *name << endl;
	}

	string select;
	cout << "Selection: ";
	cin >> select;

	string open = openLobby(select);
	cout << open << endl;

	system("pause");
}

string openLobby(string select)
{
	for (list<string>::iterator name = lobbyList.begin(); name != lobbyList.end(); name++)
	{
		if (*name == select)
		{
			return *name;
		}
	}
	cout << "Lobby does not exist." << endl;
	joinLobby();
}

int main()
{
	init();

	//system("pause");
	return 0;
}