#include "GameScene.h"
#include "Singletion.h"
#include "DB\WeaponDB.h"
#include "DataManager.h"
#include "Tool.h"

#include "GameMenuUI.h"

#include <AudioEngine.h>

#define TAG_HPBAR 1000

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


GameScene::~GameScene()
{
	delete player;
	delete gamemap;
	delete enemy;

	enemylist.clear();

}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MoveLayer = Point(0, 0);
	foreViewPoint = Point(0, 0);
	////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object

	gamelayer = Layer::create();
	gamelayer->retain();
	menulayer = Layer::create();
	menulayer->retain();

	auto clickedpoint = Sprite::create("clickedpoint.png");
	clickedpoint->setGlobalZOrder(10);
	clickedpoint->retain();
	clickedpoint->setScale(3);
	clickedpoint->setTag(10);
	clickedpoint->setVisible(false);

	auto MapPoint = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);


	tmap = TMXTiledMap::create(Singleton<DataManager>::getInstance()->getMapName());
	tmap->retain();
	tmap->setScale(3);

	for (int i = 0; i < 5; i++)
		layer[i] = tmap->getLayer(StringUtils::format("Layer%d", i + 1));

	layer[3]->setGlobalZOrder(5);
	layer[4]->setVisible(false);

	auto objects = tmap->getObjectGroup("Object");

	ValueMap spawnPoint = objects->getObject("SpwanPoint");

	auto enemyobjects = tmap->getObjectGroup("Enemy");
	auto enemys = enemyobjects->getObjects();


	float x = spawnPoint["x"].asFloat() * 3;
	float y = spawnPoint["y"].asFloat() * 3;

	gamemap1 = new GameMap( tmap );
	gamemap = gamemap1;

	this->addChild(gamelayer);
	gamelayer->addChild(tmap, 0, 11);
	gamelayer->addChild(clickedpoint);

	for (auto& enemyobj : enemys)
	{
		ValueMap& enemyMap = enemyobj.asValueMap();

		float x = enemyMap["x"].asFloat() * 3;
		float y = enemyMap["y"].asFloat() * 3;

		Point tileCoord = this->tileCoordForPosition(Point(x, y));

		gamemap->setAttribute(tileCoord.x, tileCoord.y, 1);
	}

	for (auto& enemyobj : enemys)
	{
		ValueMap& enemyMap = enemyobj.asValueMap();

		float x = enemyMap["x"].asFloat() * 3;
		float y = enemyMap["y"].asFloat() * 3;

		Point tileCoord = this->tileCoordForPosition(Point(x, y));

		enemy = new Enemy(gamelayer, gamemap);
		enemy->getSprite()->setPosition(PositionFortileCoord(tileCoord));
		enemy->getSprite()->setZOrder(1);
		enemylist.push_back(enemy);
	}

	player = new Player(gamelayer, gamemap);

	Weapon* startWeapon = new Weapon(Singleton<DataManager>::getInstance()->getIntData());

	player->getSprite()->setZOrder(2);
	player->setWeapon(startWeapon);

	setPlayerPosition(Point(x, y));

	this->addChild(menulayer);

	gamemenuUI = new GameMenuUI(menulayer);

	this->schedule(schedule_selector(GameScene::gameLogic), 0.2);
	this->schedule(schedule_selector(GameScene::gameLogic2), 0.4);

	return true;
}


void GameScene::gameLogic2(float dt)
{
	for (int i = 0; i < enemylist.size(); i++)
	{
		if (Tool::NearObject2(player, enemylist[i], 5))		// Enemy와 Player의 거리가 3이하일때
		{
			enemylist[i]->setExclam(1);

			if (Tool::NearObject(player, enemylist[i]))
			{
				int temp = player->getHp();

				enemylist[i]->setState(ATTACK);
				enemylist[i]->attack(player, dt);

				gamemenuUI->setMenuHp(temp, player->getHp());
				/*
				ProgressFromTo* progresstest = ProgressFromTo::create(2, temp, player->getHp());	// 체력바 임의로 만들었음
				menulayer->getChildByTag(TAG_HPBAR)->runAction(progresstest);
				*/
			}
			else
			{
				enemylist[i]->setPointAim(player->getTilePoint());
				enemylist[i]->setState(WALK);
			}

		}
		else
		{
			enemylist[i]->setExclam(2);
			enemylist[i]->setState(IDLE);
		}


		enemylist[i]->setGameMap(gamemap);
		enemylist[i]->update(dt);
		enemylist[i]->render(dt);
	}
}

void GameScene::gameLogic(float dt)
{
	gamemenuUI->setMenuCoin(100);

	player->setGameMap(gamemap);
	player->update(dt);
	player->render(dt);

	for (int i = 0; i < enemylist.size(); i++)
	{
		if (enemylist[i]->getTilePoint().y > player->getTilePoint().y)
			enemylist[i]->getSprite()->setZOrder(3);
		else
			enemylist[i]->getSprite()->setZOrder(1);

		if (!player->getFlagTouch())
		{
				if (Tool::NearObject(player, enemylist[i]))
				{
					if (!player->getIsTarget())
					{
						player->setTarget(enemylist[i]);
					}
					else
					{
						player->setState(ATTACK);
						player->attack(player->getTarget(), dt);
					}
			}
		}

		if (enemylist[i]->getState() == DEAD)
			enemylist.erase(enemylist.begin() + i);
	}

	if (player->getFlagTouch()) {}
	else
		gamelayer->getChildByTag(10)->setVisible(false);

	MoveLayer = this->setViewPointCenter(gamelayer, player->getSprite()->getPosition());
}

Point GameScene::tileCoordForPosition(Point position)
{
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height - position.y) \
		/ tmap->getTileSize().height);
	return Point(x, y);
}

cocos2d::Point GameScene::PositionFortileCoord(cocos2d::Point position)
{
	int x = (position.x * tmap->getTileSize().width) + tmap->getTileSize().width / 2;
	int y = (tmap->getMapSize().height * tmap->getTileSize().height) -
		(position.y * tmap->getTileSize().height) - tmap->getTileSize().height / 2;
	return Point(x, y);
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{

	auto touchPoint = touch->getLocation();
	Point EndPoint = tileCoordForPosition(touchPoint);
	auto PlayerPosition = tileCoordForPosition(player->getSprite()->getPosition());

	Point RealEndPoint = Point(EndPoint.x - MoveLayer.x, EndPoint.y - MoveLayer.y + tmap->getMapSize().height);

	player->setFlagTouch(true);
	player->setState(WALK);
	player->setPointAim( RealEndPoint );
	player->getAstar()->setPathFinder(false);

	gamelayer->getChildByTag(10)->setVisible(true);
	gamelayer->getChildByTag(10)->setPosition(PositionFortileCoord(RealEndPoint));

	return true;
}


Point GameScene::setViewPointCenter(Layer *layer, cocos2d::Point position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * this->tmap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (tmap->getMapSize().height * this->tmap->getTileSize().height) - visibleSize.height / 2);

	Point acutalPosition = ccp(x, y);
	Point centerOfView = ccp(visibleSize.width / 2, visibleSize.height / 2);
	Point viewPoint = ccpSub(centerOfView, acutalPosition);

	if (viewPoint - foreViewPoint != Point (0,0))
	{
		Action* action = NULL;
		action = MoveBy::create(0.2, viewPoint - foreViewPoint);
		layer->runAction(action);
	}

	foreViewPoint = viewPoint;

	return tileCoordForPosition(viewPoint);
}

void GameScene::setPlayerPosition(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);

	player->getSprite()->setPosition(PositionFortileCoord(tileCoord));
}


void GameScene::onEnter()
{
	Layer::onEnter();

	listener = EventListenerTouchOneByOne::create();
	listener->setEnabled(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void GameScene::onExit()
{
	_eventDispatcher->removeEventListener(listener);

	Layer::onExit();
}

