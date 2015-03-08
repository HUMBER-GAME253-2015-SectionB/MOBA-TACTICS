//Author:	Nicholas Higa
//Date:		3/4/2014(NH), 3/8/2014 (NH)
#include "TileSet.h"

TileSet::TileSet()
{

}

void TileSet::Initialize(char *spritePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren)
{
	tileSetSprite = new Sprite(std::string(spritePath), ren, vec2(0, 0));
	tileWidth = _tileWidth;
	tileHeight = _tileHeight;
	numWidth = tileSetSprite->GetWidth() / _tileWidth;
	numHeight = tileSetSprite->GetHeight() / _tileHeight;
}

TileSet::~TileSet()
{
	delete tileSetSprite;
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

Sprite* TileSet::GetTileSetSprite() const
{
	return tileSetSprite;
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

void TileSet::SetTileSetSprite(Sprite *sprite)
{
	tileSetSprite = sprite;
}