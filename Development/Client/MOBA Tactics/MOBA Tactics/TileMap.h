//Author:	Nicholas Higa
//Date:		3/4/2015(NH), 3/8/2015(NH), 3/10/2015(NH), 3/15/2015 (NH), 3/24/2015(NH)
//			4/8/2015(NH)
#pragma once

#include "tinyxml2.h"
#include <vector>
#include "Tile.h"
#include "TileSet.h"
#include "ITileMap.h"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;
using namespace tinyxml2;

struct HighlightTexture
{
	Sprite *sprite;
	Uint8 minAlpha;
	Uint8 maxAlpha;
	Uint8 r, g, b, alpha;
	Uint8 fadePerFrame;
	bool isFadingOut;
};

class TileMap : public ITileMap, public Sprite
{
public:
	TileMap(char *xmlFilePath, vec2 _origin, SDL_Renderer *ren);
	TileMap(char *xmlFilePath, vec2 _origin, int _mainLayer, SDL_Renderer *ren);
	TileMap(char *xmlFilePath, vec2 origin, string highlightTexturePath, SDL_Renderer *ren);
	TileMap(char *xmlFilePath, vec2 _origin, int _mainLayer, string highlightTexturePath, SDL_Renderer *ren);
	bool LoadFromFile(char *xmlFilePath, vec2 origin, SDL_Renderer *ren);
	void InitTileMap(unsigned _numWidth, unsigned _numHeight, unsigned _numLayers, unsigned _tileWidth, unsigned _tileHeight);
	void InitTileSet(char *texturePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren);
	void InitHightlightSprite(string highlightTexturePath, Uint8 r, Uint8 g, Uint8 b, Uint8 minAlpha, Uint8 maxAlpha, Uint8 fadePerFrame, SDL_Renderer *ren);
	void SetIsTileSelected(bool isSelected, int layer, int row, int col);
	void SetIsTileSelected(bool isSelected, int row, int col);
	void SetIsTileHighlighted(bool isHighlighted, int layer, int row, int col);
	void SetIsTileHighlighted(bool isHighlighted, int row, int col);
	void Draw(vec2 pos, SDL_Renderer *ren);
	void Draw(SDL_Renderer *ren);
	void DrawTile(int layer, int row, int col, SDL_Renderer *ren);
	void DrawTile(vec2 pos, int layer, int row, int col, SDL_Renderer *ren);
	bool IsPointOnMap(int mX, int mY);
	bool IsPointOnMap(vec2 _origin, int mX, int mY);
	bool IsPointOnMap(vec2 _origin, int mX, int mY, float scale);
	void Update();
	
	vec2 ConvertTileToScreenCoordinate(vec2 tileCoord); //Conversion from Tile coordinates ie (1, 3) will be converted to a screen position ie (32, 64) on the screen
	vec2 ConvertScreenToTileCoordinates(vec2 screenCoord); //Conversion from screen position ie (32, 64) will be convrted to a Tile coordinate ie (1, 3)

	vec2 ConvertTileToScreenCoordinate(vec2 _origin, vec2 tileCoord);
	vec2 ConvertScreenToTileCoordinates(vec2 _origin, vec2 screenCoord);

	vec2 ConvertTileToScreenCoordinate(vec2 _origin, vec2 tileCoord, float scale);
	vec2 ConvertScreenToTileCoordinates(vec2 _origin, vec2 screenCoord, float scale);

	void MoveMap(int x, int y); //Should not use in final project, works but not efficient.

	vec2 GetOrigin(); //World position origin, which is at the very top corner of the map.
	unsigned GetNumWidth() const;	
	unsigned GetNumHeight() const;
	unsigned GetNumLayers() const;
	unsigned GetTileWidth() const;
	unsigned GetTileHeight() const;
	TileSet* GetTileSet() const;
	Tile* GetTileAt(int layer, int row, int col);
	Tile* GetTileAt(int row, int col);
	vector<vector<vector<Tile>>>* GetTileMap();

	void SetOrigin(vec2 pos);
	void SetNumWidth(unsigned num);
	void SetNumHeight(unsigned num);
	void SetNumLayers(unsigned num);
	void SetTileWidth(unsigned num);
	void SetTileHeight(unsigned num);
	void SetTileSet(TileSet *_tileSet);
	void SetTileMap(vector<vector<vector<Tile>>> *_tileMap);
	void SetHighlightColor(Uint8 r, Uint8 g, Uint8 b);

	~TileMap();

private:
	int mainLayer;
	vector<vector<vector<Tile>>> tileMap;
	TileSet* tileSet;
	HighlightTexture hlTexture;
	vec2 origin;
	unsigned numWidth;
	unsigned numHeight;
	unsigned numLayers;
	unsigned tileWidth;
	unsigned tileHeight;
};