#pragma once

#include "cocos2d.h"
#include "Singletion.h"

struct WeaponData
{
	int id;
	int power;
	std::string name;
	std::string path;
};

class WeaponDB : public Singleton<WeaponDB>
{
private:
	std::vector<WeaponData> vWeapon;
public:
	WeaponDB();
	virtual ~WeaponDB();

	WeaponData getWeaponData( int _id );

	int getWeaponDBSize() { return vWeapon.size(); }

	void Show();
};