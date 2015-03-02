#include "Tile.h"

Tile::Tile()
{
	InitializeTile(0, vec2(0, 0), 0, 0);
}

Tile::Tile(int _tileNumber, vec2 _pos, unsigned _tileWidth, unsigned _tileHeight)
{
	InitializeTile(_tileNumber, _pos, _tileWidth, _tileHeight);
}

void Tile::InitializeTile(int _tileNumber, vec2 _pos, unsigned _tileWidth, unsigned _tileHeight)
{
	SetTileNumber(_tileNumber);
	SetPosition(_pos);
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

int Tile::GetTileNumber() const
{
	return tileNumber;
}

vec2 Tile::GetPosition() const
{
	return position;
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

void Tile::SetTileNumber(int num)
{
	tileNumber = num;
}

void Tile::SetPosition(vec2 _pos)
{
	position = _pos;
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