#pragma once

#include "cocos2d.h"
#include "Singletion.h"

class Player;

class DataManager : public Singleton<DataManager>
{
private:
	Player* player_data;
	char *str;
	int intData;
	std::string _mapname;

	int m_coin;

public:
	DataManager();
	virtual ~DataManager();

	void saveStrData(char *_str) { this->str = _str; }
	char* getStrData() { return this->str; }

	void saveIntData(int _i) { this->intData = _i; }
	int getIntData() { return this->intData; }

	void saveCoinData(int _coin) { this->m_coin = _coin; }
	int getCoinData() { return this->m_coin; }

	void saveMapName(std::string _str) { this->_mapname = _str; }
	std::string getMapName() { return this->_mapname; }

	void savePlayerData(Player* _player) { this->player_data = _player; }
	Player* getPlayerData() { return this->player_data; }

};