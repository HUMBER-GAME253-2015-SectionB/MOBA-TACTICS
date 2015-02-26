#ifndef __TILE__MAP__H__
#define __TILE__MAP__H__

#include "Texture.h"
#include "tinyxml2.h"
#include <vector>

using namespace std;
using namespace tinyxml2;

struct Tile
{
public:
	int tileNumber;
	int worldX;
	int worldY;
	unsigned tileWidth;
	unsigned tileHeight;
};

struct TileSet
{
public:
	Texture *tileSetTexture;
	unsigned numWidth;
	unsigned numHeight;
	unsigned tileWidth;
	unsigned tileHeight;
};

class TileMap
{
public:
	TileMap(char *xmlFilePath, int _worldX, int _worldY, SDL_Renderer *ren);
	bool LoadFromFile(char *xmlFilePath, int _worldX, int _worldY, SDL_Renderer *ren);
	void InitTileMap(unsigned _numWidth, unsigned _numHeight, unsigned _numLayers, unsigned _tileWidth, unsigned _tileHeight);
	void InitTileSet(char *texturePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren);
	void RenderTile(int layer, int row, int col, SDL_Renderer *ren);
	void RenderMap(SDL_Renderer *ren);

	void MoveMap(int x, int y); //Should not use in final project, works but not efficient.

	unsigned GetNumWidth() const;
	unsigned GetNumHeight() const;
	unsigned GetNumLayers() const;
	unsigned GetTileWidth() const;
	unsigned GetTileHeight() const;
	void SetNumWidth(unsigned num);
	void SetNumHeight(unsigned num);
	void SetNumLayers(unsigned num);
	void SetTileWidth(unsigned num);
	void SetTileHeight(unsigned num);
	~TileMap();

private:
	vector<vector<vector<Tile>>> tileMap;
	TileSet tileSet;
	unsigned numWidth;
	unsigned numHeight;
	unsigned numLayers;
	unsigned tileWidth;
	unsigned tileHeight;
};

#endif