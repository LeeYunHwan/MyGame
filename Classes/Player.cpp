#include "Player.h"
#include "Weapon.h"
#include "Pet.h"
#include "Tool.h"
#include <AudioEngine.h>
USING_NS_CC;

Player::Player(Layer *layer, GameMap * gamemap)
	: Being(layer, gamemap), _istouched(false), _istarget(false)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_objectid = PLAYER;

	this->setPower(5);
	this->setHp(100);
	this->setSpeed(0.2f);

	m_spriteobject = Sprite::create("clotharmor_01_01_01.png");
	m_spritepoint->addChild(m_spriteobject);
	m_spriteobject->setPosition(m_spritepoint->getContentSize().width / 2, m_spritepoint->getContentSize().height * 2 / 3);

	m_pointAim = tileCoordForPosition(m_spritepoint->getPosition());

	weapon = new Weapon(this);
	pet = new Pet(this);

	this->setPower(weapon->getWeaponPower());

	this->setObjectID(PLAYER);

	initAnimation(2, 4, 5, "clotharmor");
}


Player::~Player()
{
}

void Player::setGameMap(GameMap * gamemap)
{
	this->m_gamemap = gamemap;
}

void Player::update(float _dt)
{
	if (checkPointAim())
	{
		this->setFlagTouch(false);
		if( this->getState() != ATTACK )
			this->setState(IDLE);
	}

	if (this->getFlagTouch())
	{
		if (this->getAstar()->init(Node2D(this->getTilePoint().x, this->getTilePoint().y), Node2D(this->getPointAim().x, this->getPointAim().y)))
		{
			if (this->getAstar()->getNearTileColl())
			{
				this->setPointAim(this->getAstar()->getAimPoint());
			}
			this->getAstar()->update();
		}

		this->m_direction = this->m_astar->checkPathAndReturnNextNode(tileCoordForPosition(m_spritepoint->getPosition()));

		if (this->getDirection() == NOTDIRECTION)
		{	
				this->setFlagTouch(false);
				this->setState(IDLE);
		}
	}
	weapon->update( _dt);
	pet->update( _dt);

	if (this->getIsTarget())
	{
		if (!Tool::NearObject(this, this->getTarget()))
			this->setTarget(NULL);
	}
}

void Player::render(float _dt)
{
	Being::render(_dt);

	weapon->render( _dt);
	pet->render( _dt);
}

void Player::attack(Being* _object, float _dt)
{
	attack_dt = attack_dt + _dt;

	if (attack_dt >= 0.55 )
	{
		pet->attack(_object, _dt);

		_object->setHp(_object->getHp() - this->getPower());
		experimental::AudioEngine::play2d("hit2.ogg", false);

		attack_dt = 0.0f;
	}
		this->_fore_direction = (Tool::NearObjectDirection(this, _object));

		if (_object->getState() == DEAD)
		{
			this->getPet()->getEffectSprite()->setVisible(false);
			this->setTarget(NULL);
			this->setState(IDLE);
		}
}


void Player::setFlagTouch(bool istouched)
{
	this->_istouched = istouched;
}

bool Player::getFlagTouch()
{
	return this->_istouched;
}


bool Player::checkPointAim()
{
	if (this->getTilePoint() == this->getPointAim())
		return true;
	return false;
}
