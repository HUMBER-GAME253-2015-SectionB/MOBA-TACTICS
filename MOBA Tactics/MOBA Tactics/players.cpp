
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Players.h"
/*
//James Finnie
Last Updated 04/21
*/

using namespace std;

void InLobby();
void TeamSelect();
void Ready();
void Players();

int player1;
int player2;

void Players::CreateNewPlayer(int id)
{
	Player player = Player(id);
	Players::activePlayers.push_back(player);
}

void Players::RemovePlayer(int id)
{
	for(int i = 0; i < Players::activePlayers.size() - 1; i++)
	{
		if(activePlayers[i].ID == id)
		{
			activePlayers.erase(activePlayers.begin() + i);
		}
	}
}

Player Players::FindPlayerByID(int id)
{ 
	Player player;
	
	//loop through AcvitePlayers list until a matching ID number is found
	for(int i = 0; i < Players::activePlayers.size() - 1; i++)
	{
		if(activePlayers[i].ID == id)
			player = activePlayers[i];
		break; // return the player with that ID
	}

	return player;
}

void Players::GetTeams(std::string name)//may not use name, depends whats easiest or DB
{
	//gets teams saved in DB
	//stores in that players strct
}

void Players::SaveStats(int id)
{
	//saves stats to DB
}


//void InLobby()
//{
//	Players();
//}
//
//void Players()
//{
//	char input;
//	cout << "has player one joined lobby? y/n" << endl;
//	cin >> input;
//
//	switch(input)
//	{
//	case 'y':
//		cout << "Player one has joined lobby" << endl;
//		break;
//	case 'n':
//		cout << "Player one missing missing from lobby" << endl;
//		break;
//	}
//
//	char input2;
//	cout << "has player 2 joined lobby? y/n" << endl;
//	cin >> input2;
//
//	switch(input2)
//	{
//	case 'y':
//		cout << "Player 2 has joined lobby" << endl;
//		break;
//	case 'n':
//		cout << "Player 2 his missing from lobby" << endl;
//	}
//
//	player1 = input;
//	player2 = input2;
//
//	if(player1 == player2)
//	{
//		TeamSelect();
//	}
//
//}
//
//void TeamSelect()
//{
//	char team;
//	cout << "Player 1, choose team(1) or team(2)" << endl;
//	cin >> team;
//
//	switch (team)
//	{
//	case '1':
//		cout << "Player1 has chosen team1" << endl;
//		break;
//	case '2':
//		cout << "Player1 has chosen team2" << endl;
//	}
//	char teamchosen;
//	cout << "Player 2, choose team(1) or team(2)" << endl;
//	cin >> teamchosen;
//
//	switch(team)
//	{
//	case'1':
//		cout << "Player 2 has chosen team 1" << endl;
//		break;
//	case '2':
//		cout << "Player 2 has chosen team 2" << endl;
//	}
//
//	player1 = team;
//	player2 = teamchosen;
//
//	if(player1 == player2)
//	{
//		cout << "You cannot be on the same team, please reselect" << endl;
//		TeamSelect();
//	}
//	else
//		Ready();
//}
//
//void Ready()
//{
//	char player1RdyUp;
//	cout << "Player 1, ready to start the game? y/n" << endl;
//	cin >> player1RdyUp;
//
//	switch(player1RdyUp)
//	{
//	case 'y':
//		cout << "Player 1 is Ready to Start" <<endl;
//		break;
//	case'n':
//		cout << "Player 1 has failed to ready up" << endl;
//		break;
//	}
//
//	char player2RdyUp;
//	cout << "Player 2, ready to start the game? y/n" << endl;
//	cin >> player2RdyUp;
//
//	switch(player2RdyUp)
//	{
//	case 'y':
//		cout << "Player 2 is ready to start" << endl;
//		break;
//	case 'n':
//		cout << "Player 2 has failed to ready up" << endl;
//		break;
//	}
//
//	player1 = player1RdyUp;
//	player2 = player2RdyUp;
//
//	if (player1 != player2)
//	{
//		cout << "One or more players has failed to ready up" << endl;
//		Ready();
//	}
//	else
//		cout << "Let the game begin!" << endl;
//}
//
////int main()
////{
////	InLobby();
////
////	system("pause");
////	return 0;
////}
