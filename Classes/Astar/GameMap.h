#pragma once

#include "cocos2d.h"

enum { NORMAL, COLLISION, };

typedef struct GameTile
{
	int x;
	int y;
	int attribute;

}GTile;

class GameMap
{
private:
	int xSize;
	int ySize;

	int xTileSize;
	int yTileSize;

	GTile **_mapdata;
public:

	GameMap(int xSize, int ySize, int tileSize);
	GameMap(cocos2d::TMXTiledMap* map);
	~GameMap();

	friend GameMap operator+(const GameMap &ref1, const GameMap &ref2);

	void ShowTileabout();

	int getTileSizeX() const;
	int getTileSizeY() const;

	int getSizeX() const;
	int getSizeY() const;

	void setAttribute(int idX, int idY, int attr);
	int getAttribute( int idX, int idY ) const;
};