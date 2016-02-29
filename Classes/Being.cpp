#include "Being.h"
#include "Astar\AstarAlgorithm.h"

USING_NS_CC;

Being::Being(Layer *layer, GameMap * gamemap)
	: m_astar(nullptr), m_gamemap(nullptr),
	m_state(IDLE), m_direction(FRONT), _fore_direction(FRONT), m_pointObject(Point(0,0)),
	attack_dt(0.0f), _target(NULL)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_gamemap = gamemap;
	this->m_astar = new Astar(this->m_gamemap);

	m_spritepoint = Sprite::create("clear.png");
	m_spritepoint->setScale(3);
	layer->addChild(m_spritepoint);

	m_layer = layer;
}


Being::~Being()
{
	m_spriteobject->release();
}

void Being::render(float dt)
{
	if (this->getState() == WALK)
	{
		this->getGameMap()->setAttribute(this->getTilePoint().x, this->getTilePoint().y, 0);

		runAnimation(ObjectAnimation[1][this->getDirection() - 1]);

		Action* action = NULL;

		switch (this->m_direction)
		{
		case LEFT:
			action = MoveBy::create(m_speed , Point(-m_gamemap->getTileSizeX(), 0));
			break;
		case RIGHT:
			action = MoveBy::create(m_speed, Point(m_gamemap->getTileSizeX(), 0));
			break;
		case FRONT:
			action = MoveBy::create(m_speed, Point(0, -m_gamemap->getTileSizeY()));
			break;
		case BACK:
			action = MoveBy::create(m_speed, Point(0, m_gamemap->getTileSizeY()));
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
		runAnimation(ObjectAnimation[0][this->getDirection() - 1]);

		this->getGameMap()->setAttribute(this->getTilePoint().x, this->getTilePoint().y, 1);
	}
	else if (this->getState() == ATTACK)
	{
		runAnimation(ObjectAnimation[2][this->getForePlayerDirection() - 1]);

		this->getGameMap()->setAttribute(this->getTilePoint().x, this->getTilePoint().y, 1);
	}
}