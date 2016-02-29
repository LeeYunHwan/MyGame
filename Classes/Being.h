#pragma once

#include "cocos2d.h"
#include "define.h"
#include "Astar\GameMap.h"

#include "Object.h"

class GameMap;
class Astar;

class Being : public CObject
{
protected:
	cocos2d::Sprite *m_spritepoint;

	cocos2d::Point m_pointObject;
	cocos2d::Point m_pointAim;

	Astar* m_astar;
	GameMap* m_gamemap;

	STATE m_state;

	DIRECTION m_direction;
	DIRECTION _fore_direction;

	OBJECT_ID m_objectid;

	Being* _target;

	int m_hp;
	int m_power;
	float m_speed;

	float attack_dt;

	cocos2d::Layer* m_layer;

public:

	Being(cocos2d::Layer *_layer, GameMap *_gamemap);
	~Being();

	virtual void update(float _dt) = 0;
	virtual void render(float _dt);


//	virtual void initAnimation() {  };
//	cocos2d::Animation* createAnimation(int direction, int type, int spritecount, char* filepath);
//	void runAnimation(cocos2d::Animation* _animation);

	 cocos2d::Point getTilePoint() { return tileCoordForPosition(this->m_spritepoint->getPosition()); }

	 cocos2d::Point getPoint() { return this->m_pointObject; }
	 void setPoint(const cocos2d::Point _point) { this->m_pointObject = _point; }

	 Astar* getAstar() { return this->m_astar; }

	 void setGameMap(GameMap* _gamemap) { this->m_gamemap = _gamemap; }
	 GameMap* getGameMap() { return this->m_gamemap; }

	 STATE getState() { return this->m_state; }
	 void setState(const STATE _state) { this->m_state = _state; }

	 cocos2d::Point getPointAim() { return this->m_pointAim; }
	 void setPointAim(cocos2d::Point _point) { this->m_pointAim = _point; }

	DIRECTION getDirection() { return this->m_direction; }
	void setDirection(const DIRECTION _direction) { this->m_direction = _direction; }

	DIRECTION getForePlayerDirection() { return _fore_direction; }

	OBJECT_ID getObjectID() { return this->m_objectid; }
	void setObjectID(const OBJECT_ID _objectid) { this->m_objectid = _objectid; }

	cocos2d::Sprite* getSprite() { return this->m_spritepoint; }
//	virtual cocos2d::Sprite* getSpriteObject() { return this->m_spriteobject; }

	 int getHp() { return this->m_hp; }
	 void setHp(const int _hp) { this->m_hp = _hp; }

	 int getPower() { return this->m_power; }
	 void setPower( const int _power) { this->m_power = _power; }

	 float getSpeed() { return this->m_speed; }
	 void setSpeed(const float _speed) { this->m_speed = _speed; }

	void setTarget(Being* _target) { this->_target = _target; }
	Being* getTarget() { return this->_target; }

	void setLayer(cocos2d::Layer* _layer) { this->m_layer = _layer; }
	cocos2d::Layer* getLayer() { return m_layer; }
	

	bool getIsTarget()
	{
		if (this->_target == NULL)
			return false;
		else
			return true;
	}

	inline cocos2d::Point tileCoordForPosition(cocos2d::Point position)
	{
		int x = position.x / m_gamemap->getTileSizeX();
		int y = ((m_gamemap->getSizeY() * m_gamemap->getTileSizeY() - position.y) \
			/ m_gamemap->getTileSizeY());
		return cocos2d::Point(x, y);
	}

	inline cocos2d::Point PositionFortileCoord(cocos2d::Point position)
	{
		int x = (position.x * m_gamemap->getTileSizeX()) + m_gamemap->getTileSizeX() / 2;
		int y = (m_gamemap->getSizeY() * m_gamemap->getTileSizeY()) -
			(position.y * m_gamemap->getTileSizeY()) - m_gamemap->getTileSizeY() / 2;
		return cocos2d::Point(x, y);
	}
};