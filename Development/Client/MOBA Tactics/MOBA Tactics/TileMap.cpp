#include "TileMap.h"

TileMap::TileMap(char *xmlFilePath, int _worldX, int _worldY, SDL_Renderer *ren)
{
	LoadFromFile(xmlFilePath, _worldX, _worldY, ren);
}

TileMap::TileMap(char *xmlFilePath, int _worldX, int _worldY, string highlightTexturePath, SDL_Renderer *ren)
{
	LoadFromFile(xmlFilePath, _worldX, _worldY, ren);
	InitHightlightTexture(highlightTexturePath, 0, 0, 0, 10, 200, 3, ren);
}

bool TileMap::LoadFromFile(char *xmlFilePath, int _worldX, int _worldY, SDL_Renderer *ren)
{
	XMLDocument doc;
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
					int tileNum, tileWidth, tileHeight, worldX, worldY;
					element->QueryIntAttribute("gid", &tileNum);//i * GetNumWidth() + j;
					tileWidth = GetTileWidth();
					tileHeight = GetTileHeight();
					worldX = _worldX + j * (GetTileWidth() / 2) - ((i + 1) * GetTileWidth() / 2);
					worldY = _worldY + j * (GetTileHeight() / 2) + (i * GetTileHeight() / 2);

					/*temp.SetTileNumber(tileNum);
					temp.SetTileWidth(tileWidth);
					temp.SetTileHeight(tileHeight);
					temp.SetWorldX(worldX);
					temp.SetWorldY(worldY);
					temp.SetIsHighlighted(false);*/

					temp.InitializeTile(tileNum, worldX, worldY, tileWidth, tileHeight);

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

void TileMap::InitHightlightTexture(string highlightTexturePath, Uint8 r, Uint8 g, Uint8 b, Uint8 minAlpha, Uint8 maxAlpha, Uint8 fadePerFrame, SDL_Renderer *ren)
{
	hlTexture.texture = new Texture();
	hlTexture.texture->LoadFromFile(highlightTexturePath, ren);
	hlTexture.texture->SetBlendMode(SDL_BLENDMODE_BLEND);
	hlTexture.texture->SetAlpha((minAlpha + maxAlpha) / 2);
	hlTexture.alpha = (minAlpha + maxAlpha) / 2;
	hlTexture.minAlpha = minAlpha;
	hlTexture.maxAlpha = maxAlpha;
	hlTexture.fadePerFrame = fadePerFrame;
	hlTexture.isFadingOut = false;
	SetHighlightColor(r, g, b);
}

void TileMap::SetHighlightColor(Uint8 r, Uint8 g, Uint8 b)
{
	hlTexture.texture->SetColor(r, g, b);
	hlTexture.r = r;
	hlTexture.g = g;
	hlTexture.b = b;
}

//Should be noted tiles numbered 0 are empty tiles.
void TileMap::DrawTile(int layer, int row, int col, SDL_Renderer *ren)
{
	SDL_Rect rec;
	int tileSetRowCol;

	tileSetRowCol = (tileMap[layer][row][col].GetTileNumber() % tileSet.GetNumWidth());
	if (tileSetRowCol == 0)
		tileSetRowCol = tileSet.GetNumWidth();

	rec.x = tileSetRowCol * tileSet.GetTileWidth() - tileSet.GetTileWidth();
	rec.y = ((tileMap[layer][row][col].GetTileNumber() - tileSetRowCol) / tileSet.GetNumWidth()) * tileSet.GetTileHeight();
	rec.w = tileSet.GetTileWidth();
	rec.h = tileSet.GetTileHeight();

	tileSet.GetTileSetTexture()->Render(tileMap[layer][row][col].GetWorldX(), tileMap[layer][row][col].GetWorldY(), &rec, ren);

	if (tileMap[layer][row][col].GetIsHighlighted())
		hlTexture.texture->Render(tileMap[layer][row][col].GetWorldX(), tileMap[layer][row][col].GetWorldY(), NULL, ren);
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

	hlTexture.texture->SetAlpha(hlTexture.alpha);
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

vector<vector<vector<Tile>>>* TileMap::GetTileMap()
{
	return &tileMap;
}

void TileMap::SetNumWidth(unsigned num)
{
	numWidth = num;
}

void  TileMap::SetNumHeight(unsigned num)
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
	delete hlTexture.texture;
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
				tileMap[a][b][c].SetWorldX(tileMap[a][b][c].GetWorldX() + x);
				tileMap[a][b][c].SetWorldY(tileMap[a][b][c].GetWorldY() + y);
			}
		}
	}
}