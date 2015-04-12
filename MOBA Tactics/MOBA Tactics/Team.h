#include <string>
#include <vector>
#include "Character.h"
/*
//Michael Kochen, Trey Hesketh
Last Updated 03/11
*/
struct Team 
{
public:
int _TeamNumber;
	static std::vector<int> _Number;
	std::vector<Character> _Characters;
	std::string _Rank;
	bool _Wait;
	int _Score;
};