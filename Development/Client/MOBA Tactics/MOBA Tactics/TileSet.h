//Author:	Nicholas Higa
//Date:		3/4/2014(NH)
#pragma once

#include "Texture.h"
#include <string>

class TileSet
{
public:
	TileSet();
	void Initialize(char *texturePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren);
	~TileSet();

	unsigned GetNumWidth() const;
	unsigned GetNumHeight() const;
	unsigned GetTileWidth() const;
	unsigned GetTileHeight() const;
	Texture* GetTileSetTexture() const;

	void SetNumWidth(unsigned num);
	void SetNumHeight(unsigned num);
	void SetTileWidth(unsigned num);
	void SetTileHeight(unsigned num);
	void SetTileSetTexture(Texture *texture);

private:
	Texture *tileSetTexture;
	unsigned numWidth;
	unsigned numHeight;
	unsigned tileWidth;
	unsigned tileHeight;
};