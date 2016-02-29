#include "GameMenuUI.h"

#define TAG_HPBAR 1000
#define TAG_COIN 1001

USING_NS_CC;


GameMenuUI::GameMenuUI(Layer* _layer) :m_hp(100), m_coin(0)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto upbar = Sprite::create("upbar.png");
	upbar->retain();
	upbar->setScale(4.0f);
	upbar->setPosition(Point(320.0f, 22.0f));
	_layer->addChild(upbar);

	progresshpbar = ProgressTimer::create(Sprite::create("hpbar_.png"));
	progresshpbar->retain();
	progresshpbar->setType(ProgressTimerType::BAR);
	progresshpbar->setScale(2.8f);
	progresshpbar->setBarChangeRate(Point(1, 0));
	progresshpbar->setMidpoint(Point(0.0f, 20.0f));
	progresshpbar->setPosition(Point(105.0f, 20.0f));
	progresshpbar->setPercentage(m_hp);
	progresshpbar->setTag(TAG_HPBAR);
	_layer->addChild(progresshpbar);

	auto menuhpbar = Sprite::create("hpbar.png");
	menuhpbar->retain();
	menuhpbar->setScale(3.0f);
	menuhpbar->setPosition(Point(95.0f, 20.0f));
	_layer->addChild(menuhpbar);

	auto border = Sprite::create("border.png");
	border->retain();
	border->setScale(2.0f);
	border->setPosition(Point(320.0f, 180.0f));
	_layer->addChild(border);

	auto coin = Sprite::create("coin.png");
	coin->retain();
	coin->setScale(1.5f);
	coin->setPosition(Point(visibleSize.width * 3 / 4, visibleSize.height * 9 / 10));
	_layer->addChild(coin);

	coinLabel = Label::createWithTTF(StringUtils::format("%d",m_coin),"fonts/arial.ttf",20);
	coinLabel->setPosition(Point(visibleSize.width * 5 / 6, visibleSize.height * 9 / 10));
	coinLabel->setAlignment(TextHAlignment::LEFT);
//	coinLabel->setAlignment(TextHAlignment::RIGHT);
	coinLabel->setTag(TAG_COIN);
	_layer->addChild(coinLabel);

	coin->setGlobalZOrder(11);
	border->setGlobalZOrder(11);
	menuhpbar->setGlobalZOrder(11);
	progresshpbar->setGlobalZOrder(11);
	upbar->setGlobalZOrder(11);
	coinLabel->setGlobalZOrder(11);
}

void GameMenuUI::setMenuCoin(int _coin) 
{
	this->m_coin += _coin; 
	coinLabel->setString(StringUtils::format("%d", m_coin));
}

void GameMenuUI::setMenuHp(int _forehp, int _hp)
{

	ProgressFromTo* progresstest = ProgressFromTo::create(2, _forehp, _hp);	// 체력바 임의로 만들었음
	progresshpbar->runAction(progresstest);
}