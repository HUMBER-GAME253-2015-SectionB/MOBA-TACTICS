//Author:	Nicholas Higa
//Date:		3/30/2015

//Used to avoid circular references

#pragma once

class IScene
{
public:
	virtual void Init() = 0;
	virtual void LoadContent() = 0;
	virtual void UnloadContent() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};