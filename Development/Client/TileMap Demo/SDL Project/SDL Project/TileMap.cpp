#include "TileMap.h"

TileMap::TileMap(char *xmlFilePath, int _worldX, int _worldY, SDL_Renderer *ren)
{
	LoadFromFile(xmlFilePath, _worldX, _worldY, ren);
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
					element->QueryIntAttribute("gid", &temp.tileNumber);//i * GetNumWidth() + j;
					temp.tileWidth = GetTileWidth();
					temp.tileHeight = GetTileHeight();
					temp.worldX = _worldX + j * (GetTileWidth() / 2) - ((i + 1) * GetTileWidth() / 2);
					temp.worldY = _worldY + j * (GetTileHeight() / 2) + (i * GetTileHeight() / 2);
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
	tileSet.tileSetTexture = new Texture();
	tileSet.tileSetTexture->LoadFromFile(string(texturePath), ren);
	tileSet.tileWidth = _tileWidth;
	tileSet.tileHeight = _tileHeight;
	tileSet.numWidth = tileSet.tileSetTexture->GetWidth() / _tileWidth;
	tileSet.numHeight = tileSet.tileSetTexture->GetHeight() / _tileHeight;
}

//Should be noted tiles numbered 0 are empty tiles.
void TileMap::RenderTile(int layer, int row, int col, SDL_Renderer *ren)
{
	SDL_Rect rec;
	int tileSetRowCol;

	tileSetRowCol = (tileMap[layer][row][col].tileNumber % tileSet.numWidth);
	if (tileSetRowCol == 0)
		tileSetRowCol = tileSet.numWidth;
	rec.x = tileSetRowCol * tileSet.tileWidth - tileSet.tileWidth;

	rec.y = ((tileMap[layer][row][col].tileNumber - tileSetRowCol) / tileSet.numWidth) * tileSet.tileHeight;
	rec.w = tileSet.tileWidth;
	rec.h = tileSet.tileHeight;

	tileSet.tileSetTexture->Render(tileMap[layer][row][col].worldX, tileMap[layer][row][col].worldY, &rec, ren);
}

void TileMap::RenderMap(SDL_Renderer *ren)
{
	for (unsigned a = 0; a < GetNumLayers(); a++)
	{
		for (unsigned b = 0; b< GetNumHeight(); b++)
		{
			for (unsigned c = 0; c < GetNumWidth(); c++)
			{
				RenderTile(a, b, c, ren);
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

TileMap::~TileMap()
{

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
				tileMap[a][b][c].worldX += x;
				tileMap[a][b][c].worldY += y;
			}
		}
	}
}