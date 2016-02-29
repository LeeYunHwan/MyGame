#include "Pet.h"
#include "Player.h"

USING_NS_CC;

Pet::Pet(Player *_player) : CObject(), _EffectcurAnimate(nullptr), _EffectAnimation(nullptr), _EffectCurAnimation(nullptr)
{
	power = 10;

	istest = false;

	this->player = _player;

	m_spriteobject = Sprite::create("pikachu_01_01_01.png");
	player->getSpriteObject()->addChild(m_spriteobject);
	m_spriteobject->setPosition(ccp(player->getSpriteObject()->getContentSize().width * 6 / 7, player->getSpriteObject()->getContentSize().height * 2 / 3));

	m_effectsprite = Sprite::create("thunder_effect_01.png");
	player->getLayer()->addChild(m_effectsprite);
	m_effectsprite->setVisible(false);
	m_effectsprite->setScale(3);

	_EffectAnimation = createEffectAnimation(4, "thunder_effect");

	m_effectsprite->runAction(RepeatForever::create(Animate::create(_EffectAnimation)));
	m_effectsprite->setGlobalZOrder(4);
	initAnimation( 1, 2, 2, "pikachu" );
}

Pet::~Pet()
{

}


void Pet::attack( Being *_object, float _dt )
{
	m_effectsprite->setPosition(Point(_object->getSprite()->getPosition().x, _object->getSprite()->getPosition().y +10 ));

	if (istest) 
		istest = false;
	else 
		istest = true;

	m_effectsprite->setVisible(!istest);
}

void Pet::update( float dt)
{

	if (player->getDirection() == FRONT || player->getDirection() == LEFT )
		m_spriteobject->setPosition(ccp(player->getSpriteObject()->getContentSize().width * 6 / 7, player->getSpriteObject()->getContentSize().height * 2 / 3));
	else if(player->getDirection() == BACK || player->getDirection() == RIGHT)
		m_spriteobject->setPosition(ccp(player->getSpriteObject()->getContentSize().width / 7, player->getSpriteObject()->getContentSize().height * 2 / 3));

	if (player->getState() == ATTACK)
	{
		if (player->getForePlayerDirection() == FRONT || player->getForePlayerDirection() == LEFT)
			m_spriteobject->setPosition(ccp(player->getSpriteObject()->getContentSize().width * 6 / 7, player->getSpriteObject()->getContentSize().height * 2 / 3));
		else if (player->getForePlayerDirection() == BACK || player->getForePlayerDirection() == RIGHT)
			m_spriteobject->setPosition(ccp(player->getSpriteObject()->getContentSize().width / 7, player->getSpriteObject()->getContentSize().height * 2 / 3));
	}
}

void Pet::render( float dt)
{
	if (player->getState() != ATTACK)
		m_effectsprite->setVisible(false);

	if (player->getState() == WALK || player->getState() == IDLE)
	{
		runAnimation(ObjectAnimation[player->getState()][player->getDirection() - 1]);
	}
	else if (player->getState() == ATTACK)
	{
		runAnimation(ObjectAnimation[2][player->getForePlayerDirection() - 1]);
	}
}

Animation* Pet::createEffectAnimation(int spritecount, char* name)
{
	Animation *animation = Animation::create();
	for (int i = 1; i <= spritecount; ++i)
	{
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s_%02d.png", name, i)));
	}
	animation->setDelayPerUnit(0.1f);
	return animation;
}