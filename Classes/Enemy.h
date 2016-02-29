#pragma once

#include "cocos2d.h"
#include "Being.h"

class Enemy : public Being
{
private:
	bool m_bDiscovery;

	DIRECTION _fore_direction;

public:
	Enemy(cocos2d::Layer *layer, GameMap *gamemap);
	~Enemy();

	virtual void initAnimation();

	virtual void update(float dt);
	virtual void render(float dt);

	void attack( Being* _object, float dt );
	void setExclam( int flag );

	void setDiscovery(bool flag) { this->m_bDiscovery = flag; }
	bool getDiscovery() { return this->m_bDiscovery; };

};