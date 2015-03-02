#pragma once

#include "tinyxml2.h"
#include "Texture.h"
#include "Character.h"
#include "glm/glm.hpp"

using namespace std;
using namespace tinyxml2;
using namespace glm;

class Tile
{
public:
	Tile();
	Tile(int _tileNumber, vec2 _pos, unsigned _tileWidth, unsigned _tileHeight);
	void InitializeTile(int _tileNumber, vec2 _pos, unsigned _tileWidth, unsigned _tileHeight);
	void RemoveCharacter();
	~Tile();

	int GetTileNumber() const;
	vec2 GetPosition() const;
	unsigned GetTileWidth() const;
	unsigned GetTileHeight() const;
	bool GetIsOccupied() const;
	bool GetIsHighlighted() const;
	Character* GetCharacter() const;

	void SetTileNumber(int num);
	void SetPosition(vec2 _pos);
	void SetTileWidth(unsigned num);
	void SetTileHeight(unsigned num);
	void SetIsHighlighted(bool value);
	void SetCharacter(Character* _character);

private:
	int tileNumber;
	vec2 position;
	unsigned tileWidth;
	unsigned tileHeight;
	Character* character;

	bool isHighlighted;
};