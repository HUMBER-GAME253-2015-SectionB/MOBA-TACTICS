#pragma once
#include "Team.h"
#include <string>
#include <vector>

struct Player
{
	int ID; // assigned as soon as a new connection is encountered. same # as activeClient number
	std::string userName; // this should be obvious
	Team activeTeam; //team in-game
	int score; // in game score, set/reset to 0 on game start/end
	bool ready; //ready in lobby
	bool wait; // turn control
	bool connected; // check for logout
	int opponent; // refrence for various tasks, use with find player by ID
	Team storedTeams[3]; // team management/storage pre-game

	Player(){}
	Player(int id)
	{
		ID = id;
	}
};

class Players
{
public:
	static void CreateNewPlayer(int id);
	static void RemovePlayer(int id);
	static Player FindPlayerByID(int id);//returns player from list with that id#
	static void GetTeams(int id); // gets teams from database and adds them to storedTeams array;
	static void SaveStats(int id); //saves stats to DB

	//stores active players on creation, removes on logout
	static std::vector<Player> activePlayers;

private:

};

