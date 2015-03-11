//Author:	Mathieu Violette
//Date:		3/5/2015(MV)
//Used to get avoid circular references when passing Game objects.

#ifndef IGAME_H
#define IGAME_H

class IGame
{
public:
	virtual void Init() = 0;
	virtual void LoadContent() = 0;
	virtual void UnloadContent() = 0;
	//virtual void* GetCharacter();
	//virtual void* GetTileMap();
};

#endif