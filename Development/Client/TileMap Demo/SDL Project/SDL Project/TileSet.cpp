#include "TileSet.h"

TileSet::TileSet()
{

}

void TileSet::Initialize(char *texturePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren)
{
	tileSetTexture = new Texture();
	tileSetTexture->LoadFromFile(std::string(texturePath), ren);
	tileWidth = _tileWidth;
	tileHeight = _tileHeight;
	numWidth = tileSetTexture->GetWidth() / _tileWidth;
	numHeight = tileSetTexture->GetHeight() / _tileHeight;
}

TileSet::~TileSet()
{
	delete tileSetTexture;
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

Texture* TileSet::GetTileSetTexture() const
{
	return tileSetTexture;
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

void TileSet::SetTileSetTexture(Texture *texture)
{
	tileSetTexture = texture;
}