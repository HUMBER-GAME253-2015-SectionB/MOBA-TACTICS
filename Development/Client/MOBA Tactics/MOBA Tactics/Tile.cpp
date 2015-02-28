#include "Tile.h"

Tile::Tile()
{
	InitializeTile(0, 0, 0, 0, 0);
}

Tile::Tile(int _tileNumber, int _worldX, int _worldY, unsigned _tileWidth, unsigned _tileHeight)
{
	InitializeTile(_tileNumber, _worldX, _worldY, _tileWidth, _tileHeight);
}

void Tile::InitializeTile(int _tileNumber, int _worldX, int _worldY, unsigned _tileWidth, unsigned _tileHeight)
{
	SetTileNumber(_tileNumber);
	SetWorldX(_worldX);
	SetWorldY(_worldY);
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

int Tile::GetWorldX() const
{
	return worldX;
}

int Tile::GetWorldY() const
{
	return worldY;
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

void Tile::SetWorldX(int num)
{
	worldX = num;
}

void Tile::SetWorldY(int num)
{
	worldY = num;
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