//Author:	Nicholas Higa
//Date:		3/4/2014(NH)
#pragma once

#include <vector>
#include "Tile.h"
#include "TileSet.h"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

struct HighlightTexture
{
	Texture *texture;
	Uint8 minAlpha;
	Uint8 maxAlpha;
	Uint8 r, g, b, alpha;
	Uint8 fadePerFrame;
	bool isFadingOut;
};

class TileMap
{
public:
	TileMap(char *xmlFilePath, vec2 _worldPosition, SDL_Renderer *ren);
	TileMap(char *xmlFilePath, vec2 _worldPosition, string highlightTexturePath, SDL_Renderer *ren);
	bool LoadFromFile(char *xmlFilePath, vec2 _worldPosition, SDL_Renderer *ren);
	void InitTileMap(unsigned _numWidth, unsigned _numHeight, unsigned _numLayers, unsigned _tileWidth, unsigned _tileHeight);
	void InitTileSet(char *texturePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren);
	void InitHightlightTexture(string highlightTexturePath, Uint8 r, Uint8 g, Uint8 b, Uint8 minAlpha, Uint8 maxAlpha, Uint8 fadePerFrame, SDL_Renderer *ren);
	void HighlightTile(int layer, int row, int col);
	void DrawTile(int layer, int row, int col, SDL_Renderer *ren);
	void DrawMap(SDL_Renderer *ren);
	void Update();

	void MoveMap(int x, int y); //Should not use in final project, works but not efficient.

	unsigned GetNumWidth() const;	
	unsigned GetNumHeight() const;
	unsigned GetNumLayers() const;
	unsigned GetTileWidth() const;
	unsigned GetTileHeight() const;
	TileSet GetTileSet() const;
	Tile* GetTileAt(int layer, int row, int col);
	vector<vector<vector<Tile>>>* GetTileMap();

	void SetNumWidth(unsigned num);
	void SetNumHeight(unsigned num);
	void SetNumLayers(unsigned num);
	void SetTileWidth(unsigned num);
	void SetTileHeight(unsigned num);
	void SetTileSet(TileSet _tileSet);
	void SetTileMap(vector<vector<vector<Tile>>> _tileMap);
	void SetHighlightColor(Uint8 r, Uint8 g, Uint8 b);

	~TileMap();

private:
	vector<vector<vector<Tile>>> tileMap;
	TileSet tileSet;
	HighlightTexture hlTexture;
	unsigned numWidth;
	unsigned numHeight;
	unsigned numLayers;
	unsigned tileWidth;
	unsigned tileHeight;
};