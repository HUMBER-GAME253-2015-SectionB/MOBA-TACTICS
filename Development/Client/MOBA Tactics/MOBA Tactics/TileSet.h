//Author:	Nicholas Higa
//Date:		3/4/2015(NH), 3/8/2015 (NH)
#pragma once

#include "Sprite.h"
#include <string>

class TileSet
{
public:
	TileSet();
	void Initialize(char *spritePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren);
	~TileSet();

	unsigned GetNumWidth() const;
	unsigned GetNumHeight() const;
	unsigned GetTileWidth() const;
	unsigned GetTileHeight() const;
	Sprite* GetTileSetSprite() const;

	void SetNumWidth(unsigned num);
	void SetNumHeight(unsigned num);
	void SetTileWidth(unsigned num);
	void SetTileHeight(unsigned num);
	void SetTileSetSprite(Sprite *Sprite);

private:
	Sprite *tileSetSprite;
	unsigned numWidth;
	unsigned numHeight;
	unsigned tileWidth;
	unsigned tileHeight;
};