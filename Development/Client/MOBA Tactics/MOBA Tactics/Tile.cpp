#include "Tile.h"

Tile::Tile()
{
	InitializeTile(0, 0, 0, 0, 0, false);
}

Tile::Tile(int _tileNumber, int _worldX, int _worldY, unsigned _tileWidth, unsigned _tileHeight, bool _isOccupied)
{
	InitializeTile(_tileNumber, _worldX, _worldY, _tileWidth, _tileHeight, _isOccupied);
}

void Tile::InitializeTile(int _tileNumber, int _worldX, int _worldY, unsigned _tileWidth, unsigned _tileHeight, bool _isOccupied)
{
	SetTileNumber(_tileNumber);
	SetWorldX(_worldX);
	SetWorldY(_worldY);
	SetTileWidth(_tileWidth);
	SetTileHeight(_tileHeight);
	SetIsOccupied(_isOccupied);
	SetIsHighlighted(false); //Test boolean
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

bool Tile::GetIsOccupied() const
{
	return isOccupied;
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

void Tile::SetIsOccupied(bool value)
{
	isOccupied = value;
}

void Tile::SetIsHighlighted(bool value)
{
	isHighlighted = value;
}