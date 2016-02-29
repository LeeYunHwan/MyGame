#include "Tool.h"
#include <cmath>

USING_NS_CC;

size_t Tool::myStrlen(const char *src)
{
	unsigned int i = 0;

	while (src[i] != 0)
		i++;

	return i;
};

void Tool::myStrcpy(char* dest, size_t element, const char *src)
{
	const char *temp = src;
	int i = 0;
	int lenght;
	lenght = myStrlen(src);

	if (dest == NULL)
		return;
	else if (lenght >= element)
	{
		*dest = 0;
		return;
	}
	else
	{
		for (int i = 0; i < 50; i++)
		{
			*(dest + i) = *(temp + i);
			if (*(temp + i) == 0)
				break;
		}
	}
	return;
}

bool Tool::NearObject(Being *_object, Being *_object2)
{

	if ((std::abs(_object->getTilePoint().x - _object2->getTilePoint().x) + std::abs(_object->getTilePoint().y - _object2->getTilePoint().y)) <= 1)
		return true;
	return false;
};

bool Tool::NearObject2(Being *_object, Being *_object2, int dist)
{
	if (dist >= std::sqrt( std::pow(( _object->getTilePoint().x - _object2->getTilePoint().x ), 2) + std::pow((_object->getTilePoint().y - _object2->getTilePoint().y), 2)))
		return true;
	return false;
};

DIRECTION Tool::NearObjectDirection(Being *_object, Being *_object2)
{
	if (_object->getTilePoint().x - _object2->getTilePoint().x > 0)
		return LEFT;
	else if (_object->getTilePoint().x - _object2->getTilePoint().x < 0)
		return RIGHT;
	else if (_object->getTilePoint().y - _object2->getTilePoint().y > 0)
		return BACK;
	else if (_object->getTilePoint().y - _object2->getTilePoint().y < 0)
		return FRONT;
};