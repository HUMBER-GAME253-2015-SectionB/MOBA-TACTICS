//Author:	Nicholas Higa
//Date:		3/4/2015(NH), 3/8/2015 (NH), 3/15/2015 (NH)
#include "TileSet.h"

TileSet::TileSet(char *spritePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren) : Sprite(spritePath, ren, vec2(0, 0))
{
	Initialize(spritePath, _tileWidth, _tileHeight, ren);
}

void TileSet::Initialize(char *spritePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren)
{
	SetTileWidth(_tileWidth);
	SetTileHeight(_tileHeight);
	numWidth = GetWidth() / _tileWidth;
	numHeight = GetHeight() / _tileHeight;
}

TileSet::~TileSet()
{
}

unsigned TileSet::GetNumWidth() const
{
	return numWidth;
}

unsigned TileSet::GetNumHeight() const
{
	return numHeight;
}

unsigned TileSet::GetTileWidth() const
{
	return tileWidth;
}

unsigned TileSet::GetTileHeight() const
{
	return tileHeight;
}

void TileSet::SetNumWidth(unsigned num)
{
	numWidth = num;
}

void TileSet::SetNumHeight(unsigned num)
{
	numHeight = num;
}

void TileSet::SetTileWidth(unsigned num)
{
	tileWidth = num;
}

void TileSet::SetTileHeight(unsigned num)
{
	tileHeight = num;
}