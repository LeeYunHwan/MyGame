#pragma once

#include "cocos2d.h"
#include "define.h"

class CObject
{
protected:
	int id;
	int power;

	cocos2d::Sprite *m_spriteobject;

	cocos2d::Animation *ObjectAnimation[3][4];
	cocos2d::Animation *_curAnimation;
	cocos2d::Action *_curAnimate;

public:
	CObject();
	~CObject();

	virtual void update(float _dt) = 0;
	virtual void render(float _dt) = 0;

	cocos2d::Sprite* getSpriteObject() { return m_spriteobject; }

	void initAnimation(int _idleframe, int _walkframe, int _attackframe, std::string _name);
	cocos2d::Animation* createAnimation(int direction, int type, int spritecount, std::string name);
	void runAnimation(cocos2d::Animation* animation);

};