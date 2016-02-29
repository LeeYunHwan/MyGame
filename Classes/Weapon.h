#pragma once

#include "cocos2d.h"
#include "define.h"

#include "Object.h"

class Player;

class Weapon : public CObject
{
private:
	int id;
	std::string name;
	int power;
//	String resource_path;

	Player *player;


public:
	Weapon(int _id);
	Weapon( Player* _player );
	~Weapon();

	void setPlayer(Player *_player) { this->player = _player; }

	std::string getWeaponName() { return this->name; }
	int getWeaponId() { return this->id; }

	int getWeaponPower();
	void attack();
	void update( float dt );
	void render( float dt );

};