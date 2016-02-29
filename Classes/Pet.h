#pragma once

#include "cocos2d.h"
#include "define.h"
#include "Being.h"
#include "Object.h"

class CObject;
class Player;

class Pet : public CObject
{
private:
	int id;
	int power;

	Player *player;


	cocos2d::Sprite *m_effectsprite;
	cocos2d::Animation *_EffectAnimation;
	cocos2d::Animation *_EffectCurAnimation;
	cocos2d::Action *_EffectcurAnimate;


	bool istest;

public:
	Pet(Player* _player);
	~Pet();

	cocos2d::Animation* createEffectAnimation(int direction, char* name);

	void attack( Being *_object, float _dt );
	void update(float dt);
	void render(float dt);

	cocos2d::Sprite* getEffectSprite() { return m_effectsprite; }

};