//Author:	Nicholas Higa
//Date:		3/4/2015(NH), 3/10/2015(NH), 4/6/2015(NH), 4/8/2015(NH)
#include "Tile.h"

Tile::Tile()
{
	InitializeTile(0, vec2(0, 0), vec3(0, 0, 0), 0, 0);
}

Tile::Tile(int _tileID, vec2 _pos, vec3 _gridPos, unsigned _tileWidth, unsigned _tileHeight)
{
	InitializeTile(_tileID, _pos, _gridPos, _tileWidth, _tileHeight);
}

void Tile::InitializeTile(int _tileID, vec2 _pos, vec3 _gridPos, unsigned _tileWidth, unsigned _tileHeight)
{
	SetTileID(_tileID);
	SetPosition(_pos);
	SetGridPosition(_gridPos);
	SetTileWidth(_tileWidth);
	SetTileHeight(_tileHeight);
	SetIsHighlighted(false); //Test boolean
	SetCharacter(NULL);
}

void Tile::RemoveCharacter()
{
	SetCharacter(NULL);
}

Tile::~Tile()
{

}

int Tile::GetTileID() const
{
	return tileID;
}

vec2 Tile::GetPosition() const
{
	return position;
}

vec3 Tile::GetGridPosition() const
{
	return gridPosition;
}

unsigned Tile::GetTileWidth() const
{
	return tileWidth;
}

unsigned Tile::GetTileHeight() const
{
	return tileHeight;
}

Character* Tile::GetCharacter() const
{
	return character;
}

bool Tile::GetIsOccupied() const
{
	return GetCharacter() != NULL;
}

bool Tile::GetIsHighlighted() const
{
	return isHighlighted;
}

bool Tile::GetIsSelected() const
{
	return isSelected;
}

void Tile::SetTileID(int num)
{
	tileID = num;
}

void Tile::SetPosition(vec2 _pos)
{
	// This is how the tile texture/image looks like when it is loaded into the program.
	// The x position is subtracted by tileWidth / 2 so the position corresponds to the
	// top tip of the tile instead of corresponding to the top left of the texture.
	//  ____
	//  |/\| 
	//  |\/| 
	//  ----
	position = vec2(_pos.x -GetTileWidth() / 2, _pos.y);

	Character* temp = GetCharacter();
	if (GetCharacter() != NULL)
		GetCharacter()->SetOnTile(this);
}

void Tile::SetGridPosition(vec3 _gridPos)
{
	gridPosition = _gridPos;
}

void Tile::SetTileWidth(unsigned num)
{
	tileWidth = num;
}

void Tile::SetTileHeight(unsigned num)
{
	tileHeight = num;
}

void Tile::SetIsHighlighted(bool value)
{
	isHighlighted = value;
}

void Tile::SetIsSelected(bool value)
{
	isSelected = value;
}

void Tile::SetCharacter(Character* _character)
{
	character = _character;
}