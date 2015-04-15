//Coded by Marc-ANtoine Lavoie

#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Character.h"
#include "Login.h"
#include "Team.h"
#include "TeamManager.h"

struct Decoder
{
	inline static std::string Decode(int client, std::string info)
	{
#pragma region Split Words
		std::list<std::string> sections;		
		char delimiter = '/';
		int wordCount = 0;

		for (int i = 0; i < info.length(); i++)
		{
			if (info[i] == delimiter) wordCount++;
		}
		
		int iter = 0;
		for (int ii = 0; ii < wordCount; ii++)
		{
			std::string word;
			
			while (info[iter] != delimiter)
			{
				word += info[iter];
				iter++;
			}
			iter++;
			
			sections.push_back(word);
		}
#pragma endregion
#pragma region Select Method
		//get first word in list
		std::string word = sections.front();
		//get first letter of word
		char level = word.front();
		//pop first word to get second in list
		sections.pop_front();
		//get new first word in list
		word = sections.front();
		//get first letter of new word
		char method = word.front();
		sections.pop_front();
		
		switch (level)
		{
#pragma region Login Functions
		case 'l': case 'L':
			switch (method)
			{
			case 'l': case 'L':
			{
						  std::string username = sections.front();
						  sections.pop_front();
						  std::string password = sections.front();
						  //login function log(username, password)
						  return Login::TryLogin(username, password);
						  break;
			}
			case 'r': case 'R':
			{
						  std::string username = sections.front();
						  sections.pop_front();
						  std::string password = sections.front();
						  //login function log(username, password)
						  return Login::CreateNewUser(username, password);
						  break;
			}
			case 's': case 'S':
			{
						  int team = sections.front().front() - '0';
						  //start game function start(client, (int)teamNumber)
						  //hostGame(team);
						  break;
			}
			case 'j': case 'J':
			{
						  int team = sections.front().front() - '0';
						  sections.pop_front();
						  std::string host = sections.front();
						  //join game function join(client, (int)teamNumber, hostUser)
						  //joinGame(team, host);
						  break;
			}
			default:
				break;
			}
			break;
#pragma endregion
#pragma region Team Functions
		case 't': case 'T':
			switch (method)
			{
			case 'c': case 'C':
			{
						  char type[3];
						  type[0] = sections.front().front();
						  sections.pop_front();
						  type[1] = sections.front().front();
						  sections.pop_front();
						  type[3] = sections.front().front();
						  //create team function create(client, (char)character1, (char)character2, (char)character3)
						  TeamManager::CreateTeam(client, type[0], type[1], type[2]);
						  break;
			}
			case 'e': case 'E':
			{
						  char type[3];
						  int team = sections.front().front() - '0';
						  sections.pop_front();
						  type[0] = sections.front().front();
						  sections.pop_front();
						  type[1] = sections.front().front();
						  sections.pop_front();
						  type[3] = sections.front().front();
						  //edit team function edit(client, (int)teamNumber, (char)character1, (char)character2, (char)character3)
						  TeamManager::EditTeam(client, team, type[0], type[1], type[2]);
						  break;
			}
			case 'd': case 'D':
			{
						  int team = sections.front().front() - '0';
						  //delete team function delete(client, (int)teamNumber)
						  TeamManager::DeleteTeam(team);
						  break;
			}
			default:
				break;
			}
			break;
#pragma endregion
#pragma region Game Functions
		case 'g': case 'G':
			switch (method)
			{
			case 'm': case 'M':
			{
						  //move function move(characterNumber, startPoint, endPoint)
						  break;
			}
			case 'a': case 'A':
			{
						  //attack function attack(characterNumber, targetPoint)
						  break;
			}
			case 'd': case 'D':
			{
						  //defend function defend(chracterNumber)
						  break;
			}
			default:
				break;
			}
			break;
#pragma endregion
		default:
			break;
		}
#pragma endregion
	}
};