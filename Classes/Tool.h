#pragma once

#include "cocos2d.h"
#include"define.h"
#include "Being.h"
#include "Player.h"
#include "Enemy.h"

class Tool
{
public:
	static size_t myStrlen(const char *src);
	static void myStrcpy(char* dest, size_t element, const char *src);

	static bool NearObject(Being *_object, Being *_object2);
	static bool NearObject2(Being *_object, Being *_object2, int dist);
	static DIRECTION NearObjectDirection(Being *_object, Being *_object2);
};