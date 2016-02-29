#include "Weapon.h"
#include "Player.h"

#include "Singletion.h"
#include "DB\WeaponDB.h"

USING_NS_CC;

Weapon::Weapon(int _id) : CObject()
{
	this->id = _id;
	this->name = Singleton<WeaponDB>::getInstance()->getWeaponData(_id).name;
	this->power = Singleton<WeaponDB>::getInstance()->getWeaponData(_id).power;

	m_spriteobject = Sprite::create(StringUtils::format("%s_01_01_01.png", Singleton<WeaponDB>::getInstance()->getWeaponData(_id).path.c_str()));

	initAnimation(2, 4, 5, this->name);
}

Weapon::Weapon(Player *_player): CObject()
{
	power = 10;

	this->player = _player;

	m_spriteobject = Sprite::create("Weapon/goldensword/goldensword_01_01_01.png");
	player->getSpriteObject()->addChild(m_spriteobject);
	m_spriteobject->setPosition(ccp(player->getSpriteObject()->getContentSize().width/ 2, player->getSpriteObject()->getContentSize().height / 2));

	initAnimation(2, 4, 5, "goldensword");
}

Weapon::~Weapon()
{

}

int Weapon::getWeaponPower()
{
	return power;
}

void Weapon::attack()
{

}

void Weapon::update(  float dt)
{
	
}

void Weapon::render( float dt)
{
	if (player->getState() == WALK || player->getState() == IDLE)
	{
		runAnimation(ObjectAnimation[player->getState()][player->getDirection() - 1]);
	}
	else if (player->getState() == ATTACK)
	{
		runAnimation(ObjectAnimation[2][player->getForePlayerDirection() - 1]);
	}
}
