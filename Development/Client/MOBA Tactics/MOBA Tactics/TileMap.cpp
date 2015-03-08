//Author:	Nicholas Higa
//Date:		3/4/2014(NH), 3/8/2014 (NH)
#include "TileMap.h"

TileMap::TileMap(char *xmlFilePath, vec2 _worldPosition, SDL_Renderer *ren)
{
	LoadFromFile(xmlFilePath, _worldPosition, ren);
}

TileMap::TileMap(char *xmlFilePath, vec2 _worldPosition, string highlightTexturePath, SDL_Renderer *ren)
{
	LoadFromFile(xmlFilePath, _worldPosition, ren);
	InitHightlightSprite(highlightTexturePath, 0, 0, 0, 10, 200, 3, ren);
}

bool TileMap::LoadFromFile(char *xmlFilePath, vec2 _worldPosition, SDL_Renderer *ren)
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

		element = doc.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
		layerElement = doc.FirstChildElement("map")->FirstChildElement("layer");

		for (unsigned a = 0; a < GetNumLayers(); a++)
		{
			vector<vector<Tile>> tileLayer;
			for (unsigned i = 0; i < GetNumHeight(); i++)
			{
				vector<Tile> tileRow;
				for (unsigned j = 0; j < GetNumWidth(); j++)
				{
					Tile temp;
					vec2 worldPos;
					int tileNum, tileWidth, tileHeight, worldX, worldY;
					element->QueryIntAttribute("gid", &tileNum);//i * GetNumWidth() + j;
					tileWidth = GetTileWidth();
					tileHeight = GetTileHeight();
					worldPos.x = _worldPosition.x + j * (GetTileWidth() / 2) - ((i + 1) * GetTileWidth() / 2);
					worldPos.y = _worldPosition.y + j * (GetTileHeight() / 2) + (i * GetTileHeight() / 2);

					/*temp.SetTileNumber(tileNum);
					temp.SetTileWidth(tileWidth);
					temp.SetTileHeight(tileHeight);
					temp.SetWorldX(worldX);
					temp.SetWorldY(worldY);
					temp.SetIsHighlighted(false);*/

					temp.InitializeTile(tileNum, worldPos, tileWidth, tileHeight);

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
	tileSet.Initialize(texturePath, _tileWidth, _tileHeight, ren);
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

void TileMap::HighlightTile(int layer, int row, int col)
{
	GetTileMap()->at(layer).at(row).at(col).SetIsHighlighted(true);
}

//Should be noted tiles numbered 0 are empty tiles.
void TileMap::DrawTile(int layer, int row, int col, SDL_Renderer *ren)
{
	SDL_Rect rec;
	int tileSetRowCol;

	tileSetRowCol = (tileMap[layer][row][col].GetTileID() % tileSet.GetNumWidth());
	if (tileSetRowCol == 0)
		tileSetRowCol = tileSet.GetNumWidth();

	//Clipping rectangle
	rec.x = tileSetRowCol * tileSet.GetTileWidth() - tileSet.GetTileWidth();
	rec.y = ((tileMap[layer][row][col].GetTileID() - tileSetRowCol) / tileSet.GetNumWidth()) * tileSet.GetTileHeight();
	rec.w = tileSet.GetTileWidth();
	rec.h = tileSet.GetTileHeight();

	//Render destination
	SDL_Rect renderQuad;
	renderQuad.x = tileMap[layer][row][col].GetPosition().x;
	renderQuad.y = tileMap[layer][row][col].GetPosition().y;
	renderQuad.w = rec.w;
	renderQuad.h = rec.h;

	//tileSet.GetTileSetTexture()->Draw(tileMap[layer][row][col].GetPosition().x, tileMap[layer][row][col].GetPosition().y, &rec, ren);
	SDL_RenderCopy(ren, tileSet.GetTileSetSprite()->GetImage(), &rec, &renderQuad);

	if (tileMap[layer][row][col].GetIsHighlighted())
		//hlTexture.texture->Render(tileMap[layer][row][col].GetPosition().x, tileMap[layer][row][col].GetPosition().y, NULL, ren);
		SDL_RenderCopy(ren, hlTexture.sprite->GetImage(), NULL, &renderQuad);
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

void TileMap::DrawMap(SDL_Renderer *ren)
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

TileSet TileMap::GetTileSet() const
{
	return tileSet;
}

Tile* TileMap::GetTileAt(int layer, int row, int col)
{
	return &GetTileMap()->at(layer).at(row).at(col);
}

vector<vector<vector<Tile>>>* TileMap::GetTileMap()
{
	return &tileMap;
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

void TileMap::SetTileSet(TileSet _tileSet)
{
	tileSet = _tileSet;
}

void TileMap::SetTileMap(vector<vector<vector<Tile>>> _tileMap)
{
	tileMap = _tileMap;
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