#include "Object.h"

USING_NS_CC;

CObject::CObject():
_curAnimation(nullptr), _curAnimate(nullptr)
{
	power = 10;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			ObjectAnimation[i][j] = nullptr;
}

CObject::~CObject()
{
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			ObjectAnimation[i][j]->release();
}

void CObject::initAnimation(int _idleframe, int _walkframe, int _attackframe, std::string _name)
{
	for (int i = 0; i < 4; i++)
	{
		ObjectAnimation[0][i] = this->createAnimation(i + 1, 1, _idleframe, _name);
		ObjectAnimation[0][i]->retain();
	}

	for (int i = 0; i < 4; i++)
	{
		ObjectAnimation[1][i] = this->createAnimation(i + 1, 2, _walkframe, _name);
		ObjectAnimation[1][i]->retain();
	}

	for (int i = 0; i < 4; i++)
	{
		ObjectAnimation[2][i] = this->createAnimation(i + 1, 3, _attackframe, _name);
		ObjectAnimation[2][i]->retain();
	}
}

cocos2d::Animation * CObject::createAnimation(int direction, int type, int spritecount, std::string name)
{
	Animation *animation = Animation::create();
	for (int i = 1; i <= spritecount; ++i)
	{
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s_%02d_%02d_%02d.png", name.c_str(), direction, type, i)));
	}
	animation->setDelayPerUnit(0.1f);
	return animation;
}

void CObject::runAnimation(cocos2d::Animation * animation)
{

	if (_curAnimation == animation)
	{
		return;
	}

	_curAnimation = animation;
	if (_curAnimate != nullptr)
	{
		m_spriteobject->stopAction(_curAnimate);
	}

	_curAnimate = RepeatForever::create(Animate::create(animation));
	m_spriteobject->runAction(_curAnimate);
}
