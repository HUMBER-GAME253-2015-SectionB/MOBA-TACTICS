//Author:	Nicholas Higa
//Date:		3/4/2014(NH)
#pragma once

#include "tinyxml2.h"
#include "Texture.h"
#include "Character.h"
#include "glm/glm.hpp"
#include "ITile.h"

using namespace std;
using namespace tinyxml2;
using namespace glm;

class Tile : public ITile
{
public:
	Tile();
	Tile(int _tileID, vec2 _pos, unsigned _tileWidth, unsigned _tileHeight);
	void InitializeTile(int _tileID, vec2 _pos, unsigned _tileWidth, unsigned _tileHeight);
	void RemoveCharacter();
	~Tile();

	int GetTileID() const;
	vec2 GetPosition() const;
	unsigned GetTileWidth() const;
	unsigned GetTileHeight() const;
	bool GetIsOccupied() const;
	bool GetIsHighlighted() const;
	Character* GetCharacter() const;

	void SetTileID(int num);
	void SetPosition(vec2 _pos);
	void SetTileWidth(unsigned num);
	void SetTileHeight(unsigned num);
	void SetIsHighlighted(bool value);
	void SetCharacter(Character* _character);

private:
	int tileID;
	vec2 position;
	unsigned tileWidth;
	unsigned tileHeight;
	Character* character;

	bool isHighlighted;
};