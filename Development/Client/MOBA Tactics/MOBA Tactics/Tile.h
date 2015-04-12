//Author:	Nicholas Higa
//Date:		3/4/2015(NH), 3/8/2015(NH), 3/10/2015(NH), 4/6/2015(NH),
//			4/11/2015(NH)
#pragma once

#include "Character.h"
#include "glm/glm.hpp"
#include "ITile.h"

using namespace std;
using namespace glm;

class Tile : public ITile
{
public:
	Tile();
	Tile(int _tileID, vec2 _pos, vec3 _gridPos, unsigned _tileWidth, unsigned _tileHeight);
	void InitializeTile(int _tileID, vec2 _pos, vec3 _gridPos, unsigned _tileWidth, unsigned _tileHeight);
	void RemoveCharacter();
	~Tile();

	int GetTileID() const;
	vec2 GetPosition() const;
	vec2 GetGridPositionVec2() const;
	vec3 GetGridPositionVec3() const;
	unsigned GetTileWidth() const;
	unsigned GetTileHeight() const;
	bool GetIsOccupied() const;
	bool GetIsHighlighted() const;
	bool GetIsSelected() const;
	bool GetIsHovered() const;
	Character* GetCharacter() const;

	void SetTileID(int num);
	void SetPosition(vec2 _pos);
	void SetGridPosition(vec3 _gridPos);
	void SetTileWidth(unsigned num);
	void SetTileHeight(unsigned num);
	void SetIsHighlighted(bool value);
	void SetIsSelected(bool value);
	void SetIsHovered(bool value);
	void SetCharacter(Character* _character);

private:
	int tileID;
	vec2 position;
	vec3 gridPosition;
	unsigned tileWidth;
	unsigned tileHeight;
	Character* character;

	bool isHighlighted;
	bool isSelected;
	bool isHovered;
};