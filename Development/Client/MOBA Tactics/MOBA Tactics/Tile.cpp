//Author:	Nicholas Higa
//Date:		3/4/2014(NH)
#include "Tile.h"

Tile::Tile()
{
	InitializeTile(0, vec2(0, 0), vec3(0, 0, 0), 0, 0);
}

Tile::Tile(int _tileID, vec2 _pos, vec3 _gridPos, unsigned _tileWidth, unsigned _tileHeight)
{
	InitializeTile(_tileID, _pos, _gridPos, _tileWidth, _tileHeight);
}

void Tile::InitializeTile(int _tileID, vec2 _pos, vec3 _gridPos, unsigned _tileWidth, unsigned _tileHeight)
{
	SetTileID(_tileID);
	SetPosition(_pos);
	SetGridPosition(_gridPos);
	SetTileWidth(_tileWidth);
	SetTileHeight(_tileHeight);
	SetIsHighlighted(false); //Test boolean
	SetCharacter(NULL);
}

void Tile::RemoveCharacter()
{
	SetCharacter(NULL);
}

Tile::~Tile()
{

}

int Tile::GetTileID() const
{
	return tileID;
}

vec2 Tile::GetPosition() const
{
	return position;
}

vec3 Tile::GetGridPosition() const
{
	return gridPosition;
}

unsigned Tile::GetTileWidth() const
{
	return tileWidth;
}

unsigned Tile::GetTileHeight() const
{
	return tileHeight;
}

Character* Tile::GetCharacter() const
{
	return character;
}

bool Tile::GetIsOccupied() const
{
	return GetCharacter() == NULL;
}

bool Tile::GetIsHighlighted() const
{
	return isHighlighted;
}

void Tile::SetTileID(int num)
{
	tileID = num;
}

void Tile::SetPosition(vec2 _pos)
{
	position = _pos;
}

void Tile::SetGridPosition(vec3 _gridPos)
{
	gridPosition = _gridPos;
}

void Tile::SetTileWidth(unsigned num)
{
	tileWidth = num;
}

void Tile::SetTileHeight(unsigned num)
{
	tileHeight = num;
}

void Tile::SetIsHighlighted(bool value)
{
	isHighlighted = value;
}

void Tile::SetCharacter(Character* _character)
{
	character = _character;
}