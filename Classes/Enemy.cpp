#include "Enemy.h"
#include "Astar\AstarAlgorithm.h"
#include "define.h"
#include "Tool.h"

#include <AudioEngine.h>

#define EXCLAMATION_MARK 20

USING_NS_CC;

Enemy::Enemy(cocos2d::Layer *layer, GameMap *gamemap)
	:Being( layer, gamemap ), m_bDiscovery( false ), _fore_direction(FRONT)
{
	m_objectid = ENEMY;

	m_hp = 100;
	this->setPower(2);
	this->setSpeed(0.4f);

	m_spriteobject = Sprite::create("ogre_01_01_01.png");
	m_spriteobject->setPosition(m_spritepoint->getContentSize().width / 2, m_spritepoint->getContentSize().height *3 / 4);
	m_spritepoint->addChild(m_spriteobject);

	auto exclamation_mark = Sprite::create("exclamation_mark.png");
	exclamation_mark->setPosition(m_spriteobject->getContentSize().width / 2, m_spriteobject->getContentSize().height * 0.95);
	m_spriteobject->addChild(exclamation_mark);
	exclamation_mark->setVisible(false);
	exclamation_mark->setTag(EXCLAMATION_MARK);

	initAnimation();
}

Enemy::~Enemy()
{

}

void Enemy::initAnimation()
{

	ObjectAnimation[0][0] = this->createAnimation(1, 1, 2, "ogre");
	ObjectAnimation[0][0]->retain();
	ObjectAnimation[0][1] = this->createAnimation(2, 1, 2, "ogre");
	ObjectAnimation[0][1]->retain();
	ObjectAnimation[0][2] = this->createAnimation(3, 1, 2, "ogre");
	ObjectAnimation[0][2]->retain();
	ObjectAnimation[0][3] = this->createAnimation(4, 1, 2, "ogre");
	ObjectAnimation[0][3]->retain();

	ObjectAnimation[1][0] = this->createAnimation(1, 2, 6, "ogre");
	ObjectAnimation[1][0]->retain();
	ObjectAnimation[1][1] = this->createAnimation(2, 2, 5, "ogre");
	ObjectAnimation[1][1]->retain();
	ObjectAnimation[1][2] = this->createAnimation(3, 2, 6, "ogre");
	ObjectAnimation[1][2]->retain();
	ObjectAnimation[1][3] = this->createAnimation(4, 2, 6, "ogre");
	ObjectAnimation[1][3]->retain();

	ObjectAnimation[2][0] = this->createAnimation(1, 3, 3, "ogre");
	ObjectAnimation[2][0]->setDelayPerUnit(0.15f);
	ObjectAnimation[2][0]->retain();
	ObjectAnimation[2][1] = this->createAnimation(2, 3, 3, "ogre");
	ObjectAnimation[2][1]->setDelayPerUnit(0.15f);
	ObjectAnimation[2][1]->retain();
	ObjectAnimation[2][2] = this->createAnimation(3, 3, 3, "ogre");
	ObjectAnimation[2][2]->setDelayPerUnit(0.15f);
	ObjectAnimation[2][2]->retain();
	ObjectAnimation[2][3] = this->createAnimation(4, 3, 3, "ogre");
	ObjectAnimation[2][3]->setDelayPerUnit(0.15f);
	ObjectAnimation[2][3]->retain();
}

void Enemy::update(float _dt)
 {

	 if (m_bDiscovery)
	 {
		 this->getAstar()->setPathFinder(false);

		 this->getSpriteObject()->getChildByTag(EXCLAMATION_MARK)->setVisible(true);

		 if (this->getAstar()->init(Node2D(this->getTilePoint().x, this->getTilePoint().y), Node2D(this->getPointAim().x, this->getPointAim().y)))
		 {
			 if (this->getAstar()->getNearTileColl())
			 {
				 this->setPointAim(this->getAstar()->getAimPoint());
			 }
			 this->getAstar()->update();
		 }

		 this->m_direction = this->m_astar->checkPathAndReturnNextNode(tileCoordForPosition(m_spritepoint->getPosition()));
	 }
	 else
	 {
		 this->getSpriteObject()->getChildByTag(EXCLAMATION_MARK)->setVisible(false);
	 }

	 if (this->getHp() <= 0)
	 {
		 this->setState(DEAD);
	 }

	 if (this->getIsTarget())
	 {
		 if (!Tool::NearObject(this, this->getTarget()))
			 this->setTarget(NULL);
	 }

 }

void Enemy::render(float _dt)
 {
	 if (this->getState() == WALK)
	 {
		 this->getGameMap()->setAttribute(this->getTilePoint().x, this->getTilePoint().y, 0);

		 Action* action = NULL;
		 switch (this->m_direction)
		 {
		 case LEFT:
			 runAnimation(ObjectAnimation[1][2]);
			 action = MoveBy::create(0.4, Point(-m_gamemap->getTileSizeX(), 0));
			 break;
		 case RIGHT:
			 runAnimation(ObjectAnimation[1][3]);
			 action = MoveBy::create(0.4, Point(m_gamemap->getTileSizeX(), 0));
			 break;
		 case FRONT:
			 runAnimation(ObjectAnimation[1][0]);
			 action = MoveBy::create(0.4, Point(0, -m_gamemap->getTileSizeY()));
			 break;
		 case BACK:
			 runAnimation(ObjectAnimation[1][1]);
			 action = MoveBy::create(0.4, Point(0, m_gamemap->getTileSizeY()));
			 break;
		 }

		 if (this->m_direction != NOTDIRECTION)
			 m_spritepoint->runAction(action);


		 switch (this->m_direction)
		 {
		 case LEFT:
			 this->getGameMap()->setAttribute(this->getTilePoint().x - 1, this->getTilePoint().y, 1);
			 break;
		 case RIGHT:
			 this->getGameMap()->setAttribute(this->getTilePoint().x + 1, this->getTilePoint().y, 1);
			 break;
		 case FRONT:
			 this->getGameMap()->setAttribute(this->getTilePoint().x, this->getTilePoint().y + 1, 1);
			 break;
		 case BACK:
			 this->getGameMap()->setAttribute(this->getTilePoint().x, this->getTilePoint().y - 1, 1);
			 break;
		 }
	 }
	 else if (this->getState() == IDLE)
	 {
		 switch (this->m_direction)
		 {
		 case LEFT:
			 runAnimation(ObjectAnimation[0][2]);
			 break;
		 case RIGHT:
			 runAnimation(ObjectAnimation[0][3]);
			 break;
		 case FRONT:
			 runAnimation(ObjectAnimation[0][0]);
			 break;
		 case BACK:
			 runAnimation(ObjectAnimation[0][1]);
			 break;
		 }

		 this->getGameMap()->setAttribute(this->getTilePoint().x, this->getTilePoint().y, 1);

	 }
	 else if (this->getState() == ATTACK)
	 {
		 switch (this->_fore_direction)
		 {
		 case LEFT:
			 runAnimation(ObjectAnimation[2][2]);
			 break;
		 case RIGHT:
			 runAnimation(ObjectAnimation[2][3]);
			 break;
		 case FRONT:
			 runAnimation(ObjectAnimation[2][0]);
			 break;
		 case BACK:
			 runAnimation(ObjectAnimation[2][1]);
			 break;
		 }
	 }

	 if (this->getState() == DEAD)
	 {
		 Action* action = NULL;
		 action = Hide::create();
		 this->getGameMap()->setAttribute(this->getTilePoint().x, this->getTilePoint().y, 0);
		 experimental::AudioEngine::play2d("kill1.ogg", false);
		 this->getSprite()->runAction(action);
	 }
 }

void Enemy::attack( Being* _object, float dt )
{
	attack_dt = attack_dt + dt;
	if (attack_dt >= 0.30)
	{

		_object->setHp(_object->getHp() - this->getPower());
		experimental::AudioEngine::play2d("hit2.ogg", false);
		attack_dt = 0.0f;
	}

	this->getGameMap()->setAttribute(this->getTilePoint().x, this->getTilePoint().y, 1);
	this->_fore_direction = ((Tool::NearObjectDirection(this, _object)));
	this->setExclam(2);
}
void Enemy::setExclam( int flag )
{
	if (flag == 1)
		m_bDiscovery = true;
	else  if (flag == 2)
		m_bDiscovery = false;
}