#include "Singletion.h"
#include "DB\WeaponDB.h"

#include "Tool.h"

#include "ReadyScene.h"
#include "HelloWorldScene.h"
#include "define.h"

#include "ScrollMenu.h"

#include "DataManager.h"
#include "Astar\GameMap.h"
#include "Player.h"
#include "Weapon.h"


USING_NS_CC;
USING_NS_CC_EXT;

Scene* ReadyScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ReadyScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool ReadyScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Singleton<WeaponDB>::getInstance();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("clotharmor.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("thunder.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ogre.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pikachu.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("thunder_effect.plist");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	s = nullptr;

	auto backgroundSprite = Sprite::create("start_background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundSprite->setScale(3);
	this->addChild(backgroundSprite);


	auto tmap = TMXTiledMap::create("StartMap.tmx");

	gamemap = new GameMap(tmap);

	player = new Player(this, gamemap);

	player->getSpriteObject()->setScale(1.5f);
	player->getSprite()->setPosition(Point(visibleSize.width * 7 / 24, visibleSize.height /2));

	s = new Weapon(1);
	player->setWeapon(s);

	MenuItemImage* PlayMenu = MenuItemImage::create("play_button1.png", "play_button2.png", CC_CALLBACK_1(ReadyScene::onMenu, this));
	PlayMenu->setScale(2.5f);

	Menu* menu = Menu::create(PlayMenu, NULL);
	menu->setPosition(visibleSize.width * 0.3f, visibleSize.height * 0.3f);
	this->addChild(menu, 1);

	MenuItemImage* LeftButton = MenuItemImage::create("left_button1.png", "left_button2.png", CC_CALLBACK_1(ReadyScene::onLeftButton, this));
	LeftButton->setScale(2.5f);

	Menu* left_bt = Menu::create(LeftButton, NULL);
	left_bt->setPosition(Point(visibleSize.width / 6, visibleSize.height / 2));
	this->addChild(left_bt, 1);

	MenuItemImage* RightButton = MenuItemImage::create("right_button1.png", "right_button2.png", CC_CALLBACK_1(ReadyScene::onRightButton, this));
	RightButton->setScale(2.5f);

	Menu* right_bt = Menu::create(RightButton, NULL);
	right_bt->setPosition(Point(visibleSize.width * 3 / 7, visibleSize.height   / 2));
	this->addChild(right_bt, 1);


	auto weapon_sprite = Sprite::create("weapon_font.png");
	weapon_sprite->setScale(2.0f);
	weapon_sprite->setPosition(Point(visibleSize.width * 0.55f, visibleSize.height * 0.75f));
	this->addChild(weapon_sprite);

	auto scrollView = ScrollView::create(Size(Singleton<WeaponDB>::getInstance()->getWeaponDBSize() * 48, 48));
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setContentOffset(Vec2(0, 0));
	scrollView->setContentOffsetInDuration(Vec2(0, 0), 10.f);
	scrollView->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.6f));
	this->addChild(scrollView);

	
	MenuItemImage *test;
	Menu *menutest;

	for (int i = 1; i <= Singleton<WeaponDB>::getInstance()->getWeaponDBSize(); i++)
	{
		std::string str = StringUtils::format("%s_menu.png", Singleton<WeaponDB>::getInstance()->getWeaponData(i).path.c_str());

		test = MenuItemImage::create(str, str, CC_CALLBACK_1(ReadyScene::test2, this));
		test->setScale(2.5f);
		test->setTag(i);

		menutest = ScrollMenu::create(test, NULL);
		menutest->setPosition(Point((48 * i), 20));
		scrollView->addChild(menutest);
	}

	this->schedule(schedule_selector(ReadyScene::gameLogic), 0.2);

	return true;

}

void ReadyScene::onLeftButton(Ref *sender)
{
	switch (player->getDirection())
	{
	case FRONT:
		player->setDirection(LEFT);
		break;
	case LEFT:
		player->setDirection(BACK);
		break;
	case BACK:
		player->setDirection(RIGHT);
		break;
	case RIGHT:
		player->setDirection(FRONT);
		break;
	}
}

void ReadyScene::onRightButton(Ref *sender)
{
	switch (player->getDirection())
	{
	case FRONT:
		player->setDirection(RIGHT);
		break;
	case LEFT:
		player->setDirection(FRONT);
		break;
	case BACK:
		player->setDirection(LEFT);
		break;
	case RIGHT:
		player->setDirection(BACK);
		break;
	}
}

void ReadyScene::onMenu(Ref *sender)
{
	Singleton<DataManager>::getInstance()->saveIntData( player->getWeapon()->getWeaponId() );

	Singleton<DataManager>::getInstance()->saveMapName("ttest.tmx");

	auto scene = HelloWorld::createScene();


	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void ReadyScene::gameLogic(float dt)
{
	player->render(dt);
}


void ReadyScene::test2(Ref *sender)
{
	player->setDirection(FRONT);

	switch (((Node*)sender)->getTag())
	{
	case 1:
		s = new Weapon(1);
		player->setWeapon(s);
		break;
	case 2:
		s = new Weapon(2);
		player->setWeapon(s);
		break;
	case 3:
		s = new Weapon(3);
		player->setWeapon(s);
		break;
	case 4:
		s = new Weapon(4);
		player->setWeapon(s);
		break;
	}
}
