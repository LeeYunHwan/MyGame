#ifndef __HelloWorld_SCENE2_H__
#define __HelloWorld_SCENE2_H__

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"

#include "Astar\AstarAlgorithm.h"
#include "Astar\GameMap.h"

#include <vector>

class HelloWorld2 : public cocos2d::Layer
{
private:
	Player* player;

	std::vector<Enemy*> enemylist;

	GameMap *gamemap;
	GameMap *gamemap1;

	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer *layer1;
	cocos2d::TMXLayer *layer2;
	cocos2d::TMXLayer *layer3;
	cocos2d::TMXLayer *layer4;
	cocos2d::TMXLayer *layer5;

	cocos2d::Layer *gamelayer;
	cocos2d::Layer *menulayer;

	cocos2d::EventListenerTouchOneByOne* listener;

	bool istouched;

	cocos2d::Point MoveLayer;
	cocos2d::Point foreViewPoint;


public:
	static cocos2d::Scene* createScene();
	virtual ~HelloWorld2();

	virtual bool init();
	//	~HelloWorld2();
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld2);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
//	virtual void onTouchCancelled(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);


	void createMenu();
	void onMenu(Ref *sender);

	void gameLogic(float dt);
	void gameLogic2(float dt);
	cocos2d::Point tileCoordForPosition(cocos2d::Point position);
	cocos2d::Point PositionFortileCoord(cocos2d::Point position);

	virtual void onEnter();
	virtual void onExit();

	cocos2d::Point setViewPointCenter(cocos2d::Layer *layer, cocos2d::Point position);
	void setPlayerPosition(cocos2d::Point position);
	void doRain();
};

#endif // __HelloWorld2_SCENE_H__
