#pragma once
#include "cocos2d.h"
#include "Astar\AstarAlgorithm.h"
#include "define.h"
#include "Being.h"
#include "Weapon.h"

class Pet;
class Weapon;

class Player : public Being
{
private:
	Weapon* weapon;
	Pet *pet;
	
	bool _istouched;
	bool _iswalking;


	bool _istarget;

public:
	Player( cocos2d::Layer *layer ,GameMap *gamemap );
	~Player();

	void setGameMap(GameMap* gamemap);
	virtual void update(float _dt);
	virtual void render(float _dt );



	void attack(Being *_object, float dt);

	void setFlagTouch(bool istouched);
	bool getFlagTouch();

	void setWeapon(Weapon* _weapon) 
	{ 
		this->weapon->getSpriteObject()->setVisible(false);
		delete this->weapon;

		this->weapon = _weapon; 
		this->weapon->setPlayer(this);
		this->getSpriteObject()->addChild(this->weapon->getSpriteObject());
		this->weapon->getSpriteObject()->setPosition(cocos2d::Point(this->getSpriteObject()->getContentSize().width / 2, this->getSpriteObject()->getContentSize().height / 2));
	}
	Weapon* getWeapon() { return this->weapon; }

	Pet* getPet() { return pet; }

	bool checkPointAim();

//	Astar* getAstar();

};

