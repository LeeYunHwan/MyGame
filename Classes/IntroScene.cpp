#include "IntroScene.h"
#include "ReadyScene.h"
#include "define.h"

#include "ScrollMenu.h"

#include "Singletion.h"
#include "DB\WeaponDB.h"

#include "Tool.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* IntroScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = IntroScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool IntroScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

//	initsocket();

	this->scheduleOnce(schedule_selector(IntroScene::GoToHelloWorldScene), DISPLAY_TIME_INTRO_SCENE);

	Singleton<WeaponDB>::getInstance();

	MenuItemImage *test;
	Menu *menutest;

	auto scrollView = ScrollView::create(Size(visibleSize.width * 0.4f, 64));
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setContentOffset(Vec2(0, 0));
	scrollView->setContentOffsetInDuration(Vec2(0, 0), 10.f);
	scrollView->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.6f));
	this->addChild(scrollView);


	test = MenuItemImage::create(StringUtils::format("%s_menu.png", Singleton<WeaponDB>::getInstance()->getWeaponData(1).path.c_str()), StringUtils::format("%s_menu.png", Singleton<WeaponDB>::getInstance()->getWeaponData(1).path.c_str()), CC_CALLBACK_1(IntroScene::test2, this));
	test->setScale(5.5f);

	menutest = ScrollMenu::create(test, NULL);
	menutest->setPosition(Point(32 + (48 ), 20));
	scrollView->addChild(menutest);



	return true;

}

/*
void IntroScene::initsocket()
{
	//	_client = SocketIO::connect(*socktest,"http://jjh6469.ddns.net:6469");
	_client = SocketIO::connect("127.0.0.1:3000", *this);

	_client->on("hello", CC_CALLBACK_2(IntroScene::onReceiveEvent, this));

}

void IntroScene::onReceiveEvent(SIOClient* client, const std::string& data) {

	log("receive");
};
*/
void IntroScene::GoToHelloWorldScene(float dt)
{

//	if (_client->Isconnect())
//		log("connect");
//	else
//		log("fail...");

//	client->emit("hello", "{ \"value\" : \"test\" }");

	auto scene = ReadyScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void IntroScene::test2(Ref *sender)
{
	log("ddddddddd");
}
