//Author:	Nicholas Higa
//Date:		3/4/2015(NH), 3/10/2015(NH)

//This class has been created to prevent circular dependance with the Character class.
#pragma once

#include "glm/glm.hpp"

using namespace glm;

class ITile
{
public:
	ITile() {}
	ITile(int _tileID, vec2 _pos, vec3 _gridPos, unsigned _tileWidth, unsigned _tileHeight) {}
	virtual void InitializeTile(int _tileID, vec2 _pos, vec3 _gridPos, unsigned _tileWidth, unsigned _tileHeight) = 0;
	virtual void RemoveCharacter() = 0;
	virtual ~ITile() {}

	virtual int GetTileID() const = 0;
	virtual vec2 GetPosition() const = 0;
	virtual vec3 GetGridPosition() const = 0;
	virtual unsigned GetTileWidth() const = 0;
	virtual unsigned GetTileHeight() const = 0;
	virtual bool GetIsOccupied() const = 0;
	virtual bool GetIsHighlighted() const = 0;

	virtual void SetTileID(int num) = 0;
	virtual void SetPosition(vec2 _pos) = 0;
	virtual void SetGridPosition(vec3 _gridPos) = 0;
	virtual void SetTileWidth(unsigned num) = 0;
	virtual void SetTileHeight(unsigned num) = 0;
	virtual void SetIsHighlighted(bool value) = 0;
	virtual void SetCharacter(void* _character) = 0;
};