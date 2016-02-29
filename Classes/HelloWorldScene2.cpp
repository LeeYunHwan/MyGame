#include "HelloWorldScene2.h"
#include "Singletion.h"
#include "DB\WeaponDB.h"
#include "DataManager.h"
#include "Tool.h"

#include <AudioEngine.h>

#define TAG_HPBAR 1000

USING_NS_CC;

Scene* HelloWorld2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

HelloWorld2::~HelloWorld2()
{
	delete player;
	delete gamemap;

	enemylist.clear();

	tmap->release();
}

// on "init" you need to initialize your instance
bool HelloWorld2::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


//	experimental::AudioEngine::play2d("ChronoTrigger_PeacefulDays.mp3",true);

	Singleton<WeaponDB>::getInstance()->Show();

	MoveLayer = Point(0, 0);
	foreViewPoint = Point(0, 0);
	////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	Size winSize = Director::sharedDirector()->getWinSize();

	gamelayer = Layer::create();
	menulayer = Layer::create();

	auto clickedpoint = Sprite::create("clickedpoint.png");
	clickedpoint->setScale(3);
	clickedpoint->setTag(10);
	clickedpoint->setVisible(false);

	auto MapPoint = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	//여기

	tmap = TMXTiledMap::create("ttest_2.tmx");
	tmap->setScale(3);


	layer1 = tmap->getLayer("Layer1");
	layer2 = tmap->getLayer("Layer2");
	layer3 = tmap->getLayer("Layer3");
	layer4 = tmap->getLayer("Layer4");
	layer5 = tmap->getLayer("Layer5");

	layer4->setGlobalZOrder(5);
	layer5->setVisible(false);

	auto objects = tmap->getObjectGroup("Object");

	ValueMap spawnPoint = objects->getObject("SpwanPoint");

	auto enemyobjects = tmap->getObjectGroup("Enemy");
	auto enemys = enemyobjects->getObjects();

	int test = enemys.size();

	log(" size : %d", test);

	float x = spawnPoint["x"].asFloat() * 3;
	float y = spawnPoint["y"].asFloat() * 3;

	gamemap1 = new GameMap( tmap );
	gamemap = gamemap1;

	this->doRain();

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

		Enemy *enemy;
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
	createMenu();

	auto upbar = Sprite::create("upbar.png");
	upbar->setScale(4.0f);
	upbar->setPosition(Point(320.0f, 22.0f));
	menulayer->addChild(upbar);

	auto progresshpbar = ProgressTimer::create(Sprite::create("hpbar_.png"));
	progresshpbar->setType(ProgressTimerType::BAR);
	progresshpbar->setScale(2.8f);
	progresshpbar->setBarChangeRate(Point(1, 0));
	progresshpbar->setMidpoint(Point(0.0f, 20.0f));
	progresshpbar->setPosition(Point(105.0f, 20.0f));
	progresshpbar->setPercentage(100.0f);
	progresshpbar->setTag(TAG_HPBAR);
	menulayer->addChild(progresshpbar);

	auto menuhpbar = Sprite::create("hpbar.png");
	menuhpbar->setScale(3.0f);
	menuhpbar->setPosition(Point(95.0f, 20.0f));
	menulayer->addChild(menuhpbar);

	auto border = Sprite::create("border.png");
	border->setScale(2.0f);
	border->setPosition(Point(320.0f, 180.0f));
	menulayer->addChild(border);

	auto coin = Sprite::create("coin.png");
	coin->setScale(1.5f);
	coin->setPosition(Point (visibleSize.width * 3 / 4,visibleSize.height * 9 / 10 ));
	menulayer->addChild(coin);

	menulayer->setGlobalZOrder(11);

	this->schedule(schedule_selector(HelloWorld2::gameLogic), 0.2);
	this->schedule(schedule_selector(HelloWorld2::gameLogic2), 0.4);

	return true;

}


void HelloWorld2::createMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	MenuItemImage* StopMenu = MenuItemImage::create("stopbutton_1.png", "stopbutton_2.png", CC_CALLBACK_1(HelloWorld2::onMenu, this));
//	StopMenu->setScale(1.5);


	Menu* menu = Menu::create(StopMenu, NULL);
	menu->setPosition(visibleSize.width * 0.05, visibleSize.height * 0.9);
	menulayer->addChild(menu, 1);

}

void HelloWorld2::onMenu(Ref *sender)
{
	log("on Menu");
}



void HelloWorld2::gameLogic2(float dt)
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

				ProgressFromTo* progresstest = ProgressFromTo::create(2, temp, player->getHp());	// 체력바 임의로 만들었음
				menulayer->getChildByTag(TAG_HPBAR)->runAction(progresstest);

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

void HelloWorld2::gameLogic(float dt)
{

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

	if (player->getFlagTouch())
	{

	}
	else
	{
		gamelayer->getChildByTag(10)->setVisible(false);
	}

	MoveLayer = this->setViewPointCenter(gamelayer, player->getSprite()->getPosition());
}

Point HelloWorld2::tileCoordForPosition(Point position)
{
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height - position.y) \
		/ tmap->getTileSize().height);
	return Point(x, y);
}

cocos2d::Point HelloWorld2::PositionFortileCoord(cocos2d::Point position)
{
	int x = (position.x * tmap->getTileSize().width) + tmap->getTileSize().width / 2;
	int y = (tmap->getMapSize().height * tmap->getTileSize().height) -
		(position.y * tmap->getTileSize().height) - tmap->getTileSize().height / 2;
	return Point(x, y);
}


bool HelloWorld2::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
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

void HelloWorld2::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{

}

void HelloWorld2::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{

}


Point HelloWorld2::setViewPointCenter(Layer *layer, cocos2d::Point position)
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

void HelloWorld2::setPlayerPosition(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);

	player->getSprite()->setPosition(PositionFortileCoord(tileCoord));
}

void HelloWorld2::doRain()
{
	
	ParticleSystem* m_emitter = ParticleRain::create();
	m_emitter->retain();

	Point p = m_emitter->getPosition();
	m_emitter->setPosition(Point(p.x, p.y - 100));
	m_emitter->setLife(4);

	auto texture = Director::getInstance()->getTextureCache()->addImage("fire.png");
	m_emitter->setTexture(texture);
	m_emitter->setScaleY(4);

	if (m_emitter != NULL)
	{
		m_emitter->setPosition(Point(240, 320));
		this->addChild(m_emitter);
	}

}


void HelloWorld2::onEnter()
{
	Layer::onEnter();

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld2::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld2::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld2::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void HelloWorld2::onExit()
{
	_eventDispatcher->removeEventListener(listener);

	Layer::onExit();
}

