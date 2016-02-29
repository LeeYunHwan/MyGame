#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"

#include "Astar\AstarAlgorithm.h"
#include "Astar\GameMap.h"

#include <vector>

class GameMenuUI;

class GameScene : public cocos2d::Layer
{
protected:
	Player* player;
	Enemy *enemy;

	std::vector<Enemy*> enemylist;

	GameMap *gamemap;
	GameMap *gamemap1;

	GameMenuUI* gamemenuUI;

	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer *layer[5];

	cocos2d::Layer *gamelayer;
	cocos2d::Layer *menulayer;

	cocos2d::EventListenerTouchOneByOne* listener;

	cocos2d::Point MoveLayer;
	cocos2d::Point foreViewPoint;

public:

	static cocos2d::Scene* createScene();

	virtual ~GameScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void gameLogic(float dt);
	void gameLogic2(float dt);
	cocos2d::Point tileCoordForPosition(cocos2d::Point position);
	cocos2d::Point PositionFortileCoord(cocos2d::Point position);

	virtual void onEnter();
	virtual void onExit();

	cocos2d::Point setViewPointCenter(cocos2d::Layer *layer, cocos2d::Point position);
	void setPlayerPosition(cocos2d::Point position);

};
