#ifndef __READY_SCENE_H__
#define __READY_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class Weapon;
class Player;
class GameMap;

class ReadyScene : public cocos2d::Layer
{
private:
	Player *player;
	GameMap *gamemap;
	Weapon *s;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	~ReadyScene() { delete player; delete gamemap; delete s; }
	CREATE_FUNC(ReadyScene);

private:
	void onLeftButton(Ref *sender);
	void onRightButton(Ref *sender);
	void onMenu(Ref *sender);
	void gameLogic(float dt);

	void test2(Ref *sender);

};

#endif 
