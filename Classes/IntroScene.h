#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

/*
#include "network\SocketIO.h"

using namespace cocos2d::network;

class SocketTest : public SocketIO::SIODelegate
{
	virtual void onConnect(SIOClient* client) {}
	virtual void onMessage(SIOClient* client, const std::string& data) {}
	virtual void onClose(SIOClient* client) {}
	virtual void onError(SIOClient* client, const std::string& data) {}
};

*/
class IntroScene : public cocos2d::Layer//, public SocketTest
{
private:
	//SIOClient* _client;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

//	void onReceiveEvent(SIOClient* client, const std::string& data);

	CREATE_FUNC(IntroScene);

//	void onReceiveEvent(SIOClient* client, const std::string& data);

//	virtual void onConnect(SIOClient* client);
//	virtual void onMessage(SIOClient* client, const std::string& data);
//	virtual void onClose(SIOClient* client);
//	virtual void onError(SIOClient* client, const std::string& data);

private:

//	void initsocket();

	void GoToHelloWorldScene(float dt);
	void test2(Ref *sender);

};

#endif // __INTRO_SCENE_H__
