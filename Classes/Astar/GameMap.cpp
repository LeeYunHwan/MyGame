#include "GameMap.h"

GameMap::GameMap(int xSize, int ySize, int tileSize)
{
	_mapdata = new GTile*[xSize];

	this->xSize = xSize;
	this->ySize = ySize;

	this->xTileSize = tileSize;
	this->yTileSize = tileSize;


	for (int i = 0; i < xSize; i++)
		_mapdata[i] = new GTile[ySize];

	for (int i = 0; i < xSize; i++)
		for (int j = 0; j < ySize; j++)
			_mapdata[i][j].attribute = NORMAL;
}

GameMap::GameMap(cocos2d::TMXTiledMap * map )
{
	this->xSize = map->getMapSize().width;
	this->ySize = map->getMapSize().height;

	this->xTileSize = map->getTileSize().width;
	this->yTileSize = map->getTileSize().height;

	_mapdata = new GTile*[xSize];

	for (int i = 0; i < xSize; i++)
		_mapdata[i] = new GTile[ySize];

	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{
			_mapdata[i][j].x = i;
			_mapdata[i][j].y = j;
			int tileGid = map->getLayer("Layer5")->tileGIDAt(cocos2d::Point(i, j));

			if (tileGid)
			{
				auto properties = map->propertiesForGID(tileGid);
				cocos2d::ValueMap temp = properties.asValueMap();

				if (!properties.isNull())
				{
					if (temp["Collision"].asString().compare("True") == 0)
					{
						_mapdata[i][j].attribute = COLLISION;
					}
					if (temp["None"].asString().compare("True") == 0)
					{
						_mapdata[i][j].attribute = NORMAL;
					}
				}
			}
			else
			{
				_mapdata[i][j].attribute = NORMAL;
			}
		}
	}
}

GameMap::~GameMap()
{
	for (int i = 0; i < xSize; i++)
		delete _mapdata[i];
	delete _mapdata;
}

GameMap operator+(const GameMap &ref1, const GameMap &ref2)
{
	GameMap gamemap(ref1.getSizeX(), ref1.getSizeY(), ref1.getTileSizeX());

	int xSize = gamemap.getSizeX();
	int ySize = gamemap.getSizeY();

	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{
			if (ref1.getAttribute(i,j) != NORMAL)
			{
				gamemap.setAttribute(i, j, ref1.getAttribute(i, j));
			}

			if (ref2.getAttribute(i, j) != NORMAL)
			{
				gamemap.setAttribute(i, j, ref2.getAttribute(i, j));
			}
		}
	}

	return gamemap;
}

void GameMap::ShowTileabout()
{
	for (int i = 0; i < ySize; i++)
	{
		cocos2d::log("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", _mapdata[0][i].attribute, _mapdata[1][i].attribute, _mapdata[2][i].attribute, _mapdata[3][i].attribute \
			, _mapdata[4][i].attribute, _mapdata[5][i].attribute, _mapdata[6][i].attribute, _mapdata[7][i].attribute, _mapdata[8][i].attribute, _mapdata[9][i].attribute, _mapdata[10][i].attribute, _mapdata[11][i].attribute\
			, _mapdata[12][i].attribute, _mapdata[13][i].attribute, _mapdata[14][i].attribute, _mapdata[15][i].attribute, _mapdata[16][i].attribute, _mapdata[17][i].attribute, _mapdata[18][i].attribute, _mapdata[19][i].attribute);
	}

}

int GameMap::getTileSizeX() const
{
	return xTileSize;
}

int GameMap::getTileSizeY() const
{
	return yTileSize;
}

int GameMap::getSizeX() const
{
	return xSize;
}

int GameMap::getSizeY() const
{
	return ySize;
}

void GameMap::setAttribute(int idX, int idY, int attr)
{
	_mapdata[idX][idY].attribute = attr;
}

int GameMap::getAttribute( int idX, int idY ) const
{
	return _mapdata[idX][idY].attribute;
}


