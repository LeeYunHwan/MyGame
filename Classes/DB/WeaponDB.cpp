#include<fstream>
#include "Tool.h"
#include "WeaponDB.h"
#include "json\json.h"

USING_NS_CC;

WeaponDB::WeaponDB()
{

	Json::Value root;
	Json::Reader reader;


	std::string  json =  FileUtils::getInstance()->getStringFromFile("weaponDB.json");

	bool parsingSuccessful = reader.parse(json, root);

	if (!parsingSuccessful)
		return;

	Json::Value data = root["data"];

	for (auto it = data.begin(); it != data.end(); it++)
	{

		WeaponData temp;
		temp.id = (*it)["id"].asInt();
		temp.power = (*it)["power"].asInt();
		temp.name = (*it)["name"].asString();
		temp.path = (*it)["path"].asString();
		vWeapon.push_back(temp);

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(StringUtils::format("%s.plist", temp.path.c_str()));
	}

};

WeaponDB::~WeaponDB()
{

};

WeaponData WeaponDB::getWeaponData( int _id )
{
	for (auto it = vWeapon.begin(); it != vWeapon.end(); it++)
		if ((*it).id == _id)
			return (*it);	
}

void WeaponDB::Show()
{
	for (int i = 0; i < vWeapon.size(); i++)
	{
		log("%d %d %s", vWeapon[i].id, vWeapon[i].power, vWeapon[i].name.c_str());
	}
}