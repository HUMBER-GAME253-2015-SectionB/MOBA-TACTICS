//Author:	Nicholas Higa
//Date:		3/8/2015 (NH), 3/15/2015 (NH)

//This class has been created to prevent circular dependance with the Character class.
#pragma once

#include "ITile.h"
//#include "TileSet.h"
#include "glm/glm.hpp"
//#include <vector>

using namespace glm;
using namespace std;

class ITileMap
{
public:
	/*ITileMap() {}
	ITileMap(char *xmlFilePath, vec2 _worldPosition, SDL_Renderer *ren) {}
	ITileMap(char *xmlFilePath, vec2 _worldPosition, string highlightTexturePath, SDL_Renderer *ren);
	virtual ~ITileMap() {}*/

	//virtual bool LoadFromFile(char *xmlFilePath, vec2 _worldPosition, SDL_Renderer *ren) = 0;
	virtual void InitTileMap(unsigned _numWidth, unsigned _numHeight, unsigned _numLayers, unsigned _tileWidth, unsigned _tileHeight) = 0;
	//virtual void InitTileSet(char *texturePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren) = 0;
	//virtual void InitHightlightSprite(string highlightTexturePath, Uint8 r, Uint8 g, Uint8 b, Uint8 minAlpha, Uint8 maxAlpha, Uint8 fadePerFrame, SDL_Renderer *ren) = 0;
	//virtual void DrawTile(int layer, int row, int col, SDL_Renderer *ren) = 0;
	//virtual void Draw(SDL_Renderer *ren) = 0;
	virtual void Update() = 0;

	virtual unsigned GetNumWidth() const = 0;
	virtual unsigned GetNumHeight() const = 0;
	virtual unsigned GetNumLayers() const = 0;
	virtual unsigned GetTileWidth() const = 0;
	virtual unsigned GetTileHeight() const = 0;
	//virtual TileSet* GetTileSet() const = 0;
	virtual ITile* GetTileAt(int layer, int row, int col) = 0;
	//virtual vector<vector<vector<ITile*>>>* GetTileMap() = 0;

	virtual void SetIsTileHighlighted(bool isHighlighted, int layer, int row, int col) = 0;
	virtual void SetNumWidth(unsigned num) = 0;
	virtual void SetNumHeight(unsigned num) = 0;
	virtual void SetNumLayers(unsigned num) = 0;
	virtual void SetTileWidth(unsigned num) = 0;
	virtual void SetTileHeight(unsigned num) = 0;
	//virtual void SetTileSet(TileSet *_tileSet) = 0;
	//virtual void SetHighlightColor(Uint8 r, Uint8 g, Uint8 b) = 0;

	virtual bool IsPointOnMap(int mX, int mY) = 0;
	virtual bool IsPointOnMap(vec2 _origin, int mX, int mY) = 0;
};