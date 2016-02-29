#pragma once

#include "cocos2d.h"

class GameMenuUI
{
private:
	int m_hp;
	int m_coin;

	cocos2d::Label* coinLabel;
	cocos2d::ProgressTimer* progresshpbar;

public:
	GameMenuUI( cocos2d::Layer* _layer );

	void setMenuCoin(int _coin);
	void setMenuHp(int _forehp, int _hp);

};