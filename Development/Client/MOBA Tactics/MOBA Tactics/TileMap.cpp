//Author:	Nicholas Higa, Mathieu Violette
//Date:		3/4/2015(NH), 3/8/2015(NH), 3/10/2015(NH), 3/15/2015 (NH), 3/17/2015(MV),
//          3/24/2015(NH), 4/6/2015(NH), 4/8/2015(NH)

#include "TileMap.h"

TileMap::TileMap(char *xmlFilePath, vec2 _origin, SDL_Renderer *ren)
{
	LoadFromFile(xmlFilePath, _origin, ren);
	mainLayer = 1;
}

TileMap::TileMap(char *xmlFilePath, vec2 _origin, int _mainLayer, SDL_Renderer *ren)
{
	LoadFromFile(xmlFilePath, _origin, ren);
	mainLayer = _mainLayer;
}

TileMap::TileMap(char *xmlFilePath, vec2 _origin, string highlightTexturePath, SDL_Renderer *ren)
{
	LoadFromFile(xmlFilePath, _origin, ren);
	InitHightlightSprite(highlightTexturePath, 0, 0, 0, 10, 200, 3, ren);
	mainLayer = 1;
}

TileMap::TileMap(char *xmlFilePath, vec2 _origin, int _mainLayer, string highlightTexturePath, SDL_Renderer *ren)
{
	LoadFromFile(xmlFilePath, _origin, ren);
	InitHightlightSprite(highlightTexturePath, 0, 0, 0, 10, 200, 3, ren);
	mainLayer = _mainLayer;
}

bool TileMap::LoadFromFile(char *xmlFilePath, vec2 _origin, SDL_Renderer *ren)
{
	tinyxml2::XMLDocument doc;
	const char *texturePath;
	int _numWidth, _numHeight, mapTileWidth, mapTileHeight, tileSetWidth, tileSetHeight, numLayers;
	XMLElement* layerElement;
	numLayers = 0;

	try
	{
		XMLError error = doc.LoadFile(xmlFilePath);

		//Really weak error handling, only checks to see if the file at the specified location is found.
		if (error != XMLError::XML_SUCCESS)
			throw error; 

		XMLElement* element = doc.FirstChildElement("map");

		error = element->QueryIntAttribute("width", &_numWidth);
		element->QueryIntAttribute("height", &_numHeight);
		element->QueryIntAttribute("tilewidth", &mapTileWidth);
		element->QueryIntAttribute("tileheight", &mapTileHeight);

		for (XMLElement* child = doc.FirstChildElement("map")->FirstChildElement("layer"); child != NULL; child = child->NextSiblingElement())
		{
			numLayers++;
		}

		InitTileMap((unsigned)_numWidth, (unsigned)_numHeight, (unsigned)numLayers, (unsigned)mapTileWidth, (unsigned)mapTileHeight);
		
		element = doc.FirstChildElement("map")->FirstChildElement("tileset");
		element->QueryIntAttribute("tilewidth", &tileSetWidth);
		element->QueryIntAttribute("tileheight", &tileSetHeight);
		element = doc.FirstChildElement("map")->FirstChildElement("tileset")->FirstChildElement("image");
		texturePath = element->Attribute("source");

		InitTileSet((char*)texturePath, tileSetWidth, tileSetHeight, ren);
		Sprite::Initialize((char*)texturePath, ren, _origin);

		element = doc.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
		layerElement = doc.FirstChildElement("map")->FirstChildElement("layer");

		for (int i = 0; i < (int)GetNumLayers(); i++)
		{
			vector<vector<Tile>> tileLayer;
			for (int j = 0; j < (int)GetNumHeight(); j++)
			{
				vector<Tile> tileRow;
				for (int k = 0; k < (int)GetNumWidth(); k++)
				{
					Tile temp;
					int tileNum, tileWidth, tileHeight;
					element->QueryIntAttribute("gid", &tileNum);
					tileWidth = GetTileWidth();
					tileHeight = GetTileHeight();
					vec2 worldPos = ConvertTileToScreenCoordinate(vec2(k, j));
					worldPos.x -= tileWidth / 2;
					//worldPos.x = _worldPosition.x + (k - j) * (tileWidth / 2);
					//worldPos.y = _worldPosition.y + (j + k) * (tileHeight / 2);

					/*temp.SetTileNumber(tileNum);
					temp.SetTileWidth(tileWidth);
					temp.SetTileHeight(tileHeight);
					temp.SetWorldX(worldX);
					temp.SetWorldY(worldY);
					temp.SetIsHighlighted(false);*/

					temp.InitializeTile(tileNum, worldPos, vec3(i, j, k), tileWidth, tileHeight);

					tileRow.push_back(temp);

					if (element->NextSiblingElement("tile") != NULL)
						element = element->NextSiblingElement()->ToElement();
				}
				tileLayer.push_back(tileRow);
			}
			tileMap.push_back(tileLayer);

			if (layerElement->NextSiblingElement("layer") != NULL)
				layerElement = layerElement->NextSiblingElement("layer");

			element = layerElement->FirstChildElement("data")->FirstChildElement("tile");
		}

		SetOrigin(_origin);

		return true;
	}
	catch (...)
	{
		doc.PrintError();
		return false;
	}
}

void TileMap::InitTileMap(unsigned _numWidth, unsigned _numHeight, unsigned _numLayers, unsigned _tileWidth, unsigned _tileHeight)
{
	SetNumWidth(_numWidth);
	SetNumHeight(_numHeight);
	SetNumLayers(_numLayers);
	SetTileWidth(_tileWidth);
	SetTileHeight(_tileHeight);
}

void TileMap::InitTileSet(char *texturePath, unsigned _tileWidth, unsigned _tileHeight, SDL_Renderer *ren)
{
	tileSet = new TileSet(texturePath, _tileWidth, _tileHeight, ren);
}

void TileMap::InitHightlightSprite(string highlightTexturePath, Uint8 r, Uint8 g, Uint8 b, Uint8 minAlpha, Uint8 maxAlpha, Uint8 fadePerFrame, SDL_Renderer *ren)
{
	hlTexture.sprite = new Sprite(highlightTexturePath, ren, vec2(0, 0));
	hlTexture.sprite->SetBlendMode(SDL_BLENDMODE_BLEND);
	hlTexture.sprite->SetAlpha((minAlpha + maxAlpha) / 2);
	hlTexture.alpha = (minAlpha + maxAlpha) / 2;
	hlTexture.minAlpha = minAlpha;
	hlTexture.maxAlpha = maxAlpha;
	hlTexture.fadePerFrame = fadePerFrame;
	hlTexture.isFadingOut = false;
	SetHighlightColor(r, g, b);
}

void TileMap::SetHighlightColor(Uint8 r, Uint8 g, Uint8 b)
{
	hlTexture.sprite->SetColor(r, g, b);
	hlTexture.r = r;
	hlTexture.g = g;
	hlTexture.b = b;
}

void TileMap::Update()
{
	if (hlTexture.isFadingOut)
		hlTexture.alpha -= hlTexture.fadePerFrame;
	else
		hlTexture.alpha += hlTexture.fadePerFrame;

	if (hlTexture.alpha < hlTexture.minAlpha)
		hlTexture.isFadingOut = false;
	else if (hlTexture.alpha > hlTexture.maxAlpha)
		hlTexture.isFadingOut = true;

	hlTexture.sprite->SetAlpha(hlTexture.alpha);
}

void TileMap::Draw(SDL_Renderer *ren)
{
	for (unsigned a = 0; a < GetNumLayers(); a++)
	{
		for (unsigned b = 0; b< GetNumHeight(); b++)
		{
			for (unsigned c = 0; c < GetNumWidth(); c++)
			{
				DrawTile(a, b, c, ren);
			}
		}
	}
}

//Draw the map at a position different from the origin
void TileMap::Draw(vec2 pos, SDL_Renderer *ren)
{
	for (unsigned a = 0; a < GetNumLayers(); a++)
	{
		for (unsigned b = 0; b< GetNumHeight(); b++)
		{
			for (unsigned c = 0; c < GetNumWidth(); c++)
			{
				DrawTile(pos, a, b, c, ren);
			}
		}
	}
}

//Should be noted tiles numbered 0 are empty tiles.
void TileMap::DrawTile(int layer, int row, int col, SDL_Renderer *ren)
{
	SDL_Rect rec;
	int tileSetRowCol;

	tileSetRowCol = (tileMap[layer][row][col].GetTileID() % tileSet->GetNumWidth());
	if (tileSetRowCol == 0)
		tileSetRowCol = tileSet->GetNumWidth();

	//Clipping rectangle
	rec.x = tileSetRowCol * tileSet->GetTileWidth() - tileSet->GetTileWidth();
	rec.y = ((tileMap[layer][row][col].GetTileID() - tileSetRowCol) / tileSet->GetNumWidth()) * tileSet->GetTileHeight();
	rec.w = tileSet->GetTileWidth();
	rec.h = tileSet->GetTileHeight();

	//Render destination
	SDL_Rect renderQuad;
	renderQuad.x = (int)tileMap[layer][row][col].GetPosition().x;
	renderQuad.y = (int)tileMap[layer][row][col].GetPosition().y;
	renderQuad.w = rec.w;
	renderQuad.h = rec.h;

	//tileSet.GetTileSetTexture()->Draw(tileMap[layer][row][col].GetPosition().x, tileMap[layer][row][col].GetPosition().y, &rec, ren);
	SDL_RenderCopy(ren, tileSet->GetImage(), &rec, &renderQuad);

	if (tileMap[layer][row][col].GetIsHighlighted() || tileMap[layer][row][col].GetIsSelected())
		//hlTexture.texture->Render(tileMap[layer][row][col].GetPosition().x, tileMap[layer][row][col].GetPosition().y, NULL, ren);
		SDL_RenderCopy(ren, hlTexture.sprite->GetImage(), NULL, &renderQuad);
}

//Draw a tile at a position different from its set position.
void TileMap::DrawTile(vec2 pos, int layer, int row, int col, SDL_Renderer *ren)
{
	SDL_Rect rec;
	int tileSetRowCol;

	tileSetRowCol = (tileMap[layer][row][col].GetTileID() % tileSet->GetNumWidth());
	if (tileSetRowCol == 0)
		tileSetRowCol = tileSet->GetNumWidth();

	//Clipping rectangle
	rec.x = tileSetRowCol * tileSet->GetTileWidth() - tileSet->GetTileWidth();
	rec.y = ((tileMap[layer][row][col].GetTileID() - tileSetRowCol) / tileSet->GetNumWidth()) * tileSet->GetTileHeight();
	rec.w = tileSet->GetTileWidth();
	rec.h = tileSet->GetTileHeight();

	//Render destination
	SDL_Rect renderQuad;
	vec2 worldPos = ConvertTileToScreenCoordinate(pos, vec2(col, row));
	worldPos.x -= tileWidth / 2;
	renderQuad.x = (int)worldPos.x;
	renderQuad.y = (int)worldPos.y;
	renderQuad.w = rec.w;
	renderQuad.h = rec.h;

	SDL_RenderCopy(ren, tileSet->GetImage(), &rec, &renderQuad);

	if (tileMap[layer][row][col].GetIsHighlighted() || tileMap[layer][row][col].GetIsSelected())
		//hlTexture.texture->Render(tileMap[layer][row][col].GetPosition().x, tileMap[layer][row][col].GetPosition().y, NULL, ren);
		SDL_RenderCopy(ren, hlTexture.sprite->GetImage(), NULL, &renderQuad);
}

//Conversion from Tile coordinates ie (1, 3) will be converted to a screen position ie (32, 64) on the screen
vec2 TileMap::ConvertTileToScreenCoordinate(vec2 tileCoord)
{
	vec2 temp;
	temp.x = GetOrigin().x + (tileCoord.x - tileCoord.y) * GetTileWidth() / 2;
	temp.y = GetOrigin().y + (tileCoord.x + tileCoord.y) * GetTileHeight() / 2;
	return temp;
}

vec2 TileMap::ConvertTileToScreenCoordinate(vec2 _origin, vec2 tileCoord)
{
	vec2 temp;
	temp.x = _origin.x + (tileCoord.x - tileCoord.y) * GetTileWidth() / 2;
	temp.y = _origin.y + (tileCoord.x + tileCoord.y) * GetTileHeight() / 2;
	return temp;
}

vec2 TileMap::ConvertTileToScreenCoordinate(vec2 _origin, vec2 tileCoord, float scale)
{
	vec2 temp;
	temp.x = _origin.x * scale + (tileCoord.x - tileCoord.y) * GetTileWidth() / 2 * scale;
	temp.y = _origin.y * scale + (tileCoord.x + tileCoord.y) * GetTileHeight() / 2 * scale;
	return temp;
}

//Conversion from screen position ie (32, 64) will be convrted to a Tile coordinate ie (1, 3)
//This also can convert from a screen coordinate that does not correspond to a tile's corner.
//For example if the corodinate (35, 62) is within the Tile at (1, 3) this method will
//return (1, 3)
vec2 TileMap::ConvertScreenToTileCoordinates(vec2 screenCoord)
{
	vec2 temp;
	temp.x = (screenCoord.x - GetOrigin().x) / GetTileWidth() + (screenCoord.y - GetOrigin().y) / GetTileHeight();
	temp.y = (screenCoord.y - GetOrigin().y) / GetTileHeight() - (screenCoord.x - GetOrigin().x) / GetTileWidth();
	return vec2((int)temp.x, (int)temp.y);
}

vec2 TileMap::ConvertScreenToTileCoordinates(vec2 _origin, vec2 screenCoord)
{
	//Might need to include changes with scale
	vec2 temp;
	temp.x = (screenCoord.x - _origin.x) / GetTileWidth() + (screenCoord.y - _origin.y) / GetTileHeight();
	temp.y = (screenCoord.y - _origin.y) / GetTileHeight() - (screenCoord.x - _origin.x) / GetTileWidth();
	return vec2((int)temp.x, (int)temp.y);
}

vec2 TileMap::ConvertScreenToTileCoordinates(vec2 _origin, vec2 screenCoord, float scale)
{
	vec2 temp;
	temp.x = (screenCoord.x - _origin.x * scale) / (GetTileWidth() * scale) + (screenCoord.y - _origin.y * scale) / (GetTileHeight() * scale);
	temp.y = (screenCoord.y - _origin.y * scale) / (GetTileHeight() * scale) - (screenCoord.x - _origin.x * scale) / (GetTileWidth() * scale);
	return vec2((int)temp.x, (int)temp.y);
}

bool TileMap::IsPointOnMap(int mX, int mY)
{
	//Check to make sure TileID not = 0 
	vec2 tileCoord = ConvertScreenToTileCoordinates(vec2(mX, mY));
	if (tileCoord.x >= 0 && tileCoord.y >= 0 && tileCoord.x < GetNumWidth() - 1 && tileCoord.y < GetNumHeight() - 1)
		return true;
	else
		return false;
}

bool TileMap::IsPointOnMap(vec2 _origin, int mX, int mY)
{
	//Check to make sure TileID not = 0 
	vec2 tileCoord = ConvertScreenToTileCoordinates(_origin, vec2(mX, mY));
	if (tileCoord.x >= 0 && tileCoord.y >= 0 && tileCoord.x < GetNumWidth() - 1 && tileCoord.y < GetNumHeight() - 1)
		return true;
	else
		return false;
}

bool TileMap::IsPointOnMap(vec2 _origin, int mX, int mY, float scale)
{
	vec2 tileCoord = ConvertScreenToTileCoordinates(_origin, vec2(mX, mY), scale);
	if (tileCoord.x >= 0 && tileCoord.y >= 0 && tileCoord.x < GetNumWidth() - 1 && tileCoord.y < GetNumHeight() - 1)
		return true;
	else
		return false;
}

//Check if tilemap initialized before returning a value.
vec2 TileMap::GetOrigin()
{
	return origin;
}

unsigned TileMap::GetNumWidth() const
{
	return numWidth;
}

unsigned TileMap::GetNumHeight() const
{
	return numHeight;
}

unsigned TileMap::GetNumLayers() const
{
	return numLayers;
}

unsigned TileMap::GetTileWidth() const
{
	return tileWidth;
}

unsigned TileMap::GetTileHeight() const
{
	return tileHeight;
}

TileSet* TileMap::GetTileSet() const
{
	return tileSet;
}

Tile* TileMap::GetTileAt(int layer, int row, int col)
{
	if (&GetTileMap()->at(layer).at(row).at(col) != NULL)
		return &GetTileMap()->at(layer).at(row).at(col);
	else
		return NULL;
}

Tile* TileMap::GetTileAt(int row, int col)
{
	if (&GetTileMap()->at(1).at(row).at(col) != NULL)
		return &GetTileMap()->at(mainLayer).at(row).at(col);
	else
		return NULL;
}

vector<vector<vector<Tile>>>* TileMap::GetTileMap()
{
	return &tileMap;
}

void TileMap::SetIsTileHighlighted(bool isHighlighted, int layer, int row, int col)
{
	GetTileMap()->at(layer).at(row).at(col).SetIsHighlighted(isHighlighted);
}


void TileMap::SetIsTileHighlighted(bool isHighlighted, int row, int col)
{
	SetIsTileHighlighted(isHighlighted, mainLayer, row, col);
}


void TileMap::SetIsTileSelected(bool isSelected, int layer, int row, int col)
{
	GetTileMap()->at(layer).at(row).at(col).SetIsSelected(isSelected);
}

void TileMap::SetIsTileSelected(bool isSelected, int row, int col)
{
	SetIsTileSelected(isSelected, mainLayer, row, col);
}

void TileMap::SetOrigin(vec2 pos)
{
	origin = pos;
	Sprite::SetPosition(pos);

	for (unsigned a = 0; a < GetNumLayers(); a++)
	{
		for (unsigned b = 0; b< GetNumHeight(); b++)
		{
			for (unsigned c = 0; c < GetNumWidth(); c++)
			{
				tileMap[a][b][c].SetPosition(ConvertTileToScreenCoordinate(vec2(c, b)));
			}
		}
	}
}

void TileMap::SetNumWidth(unsigned num)
{
	numWidth = num;
}

void TileMap::SetNumHeight(unsigned num)
{
	numHeight = num;
}

void TileMap::SetNumLayers(unsigned num)
{
	numLayers = num;
}

void TileMap::SetTileWidth(unsigned num)
{
	tileWidth = num;
}

void TileMap::SetTileHeight(unsigned num)
{
	tileHeight = num;
}

void TileMap::SetTileSet(TileSet *_tileSet)
{
	tileSet = _tileSet;
}

void TileMap::SetTileMap(vector<vector<vector<Tile>>> *_tileMap)
{
	tileMap = *_tileMap;
}

TileMap::~TileMap()
{
	delete hlTexture.sprite;
}

//Don't think this is an efficient method since it has to update every single tile's position.
//This is just for the sake of something that works.
void TileMap::MoveMap(int x, int y)
{
	for (unsigned a = 0; a < GetNumLayers(); a++)
	{
		for (unsigned b = 0; b< GetNumHeight(); b++)
		{
			for (unsigned c = 0; c < GetNumWidth(); c++)
			{
				vec2 pos;
				pos.x = tileMap[a][b][c].GetPosition().x + x;
				pos.y = tileMap[a][b][c].GetPosition().y + y;
				tileMap[a][b][c].SetPosition(pos);
			}
		}
	}
}