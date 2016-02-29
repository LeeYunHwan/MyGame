#pragma once

#include "searchNodeInfo.h"
#include "GameMap.h"
#include "define.h"
#include <vector>
#include <cmath>

class Astar
{
private:
	typedef std::vector<searchNodeInfo*> vectorOpenList;
	typedef std::vector<searchNodeInfo*>::iterator vectorOpenListIter;

	typedef std::vector<searchNodeInfo*> vectorCloseList;
	typedef std::vector<searchNodeInfo*>::iterator vectorCloseListIter;

	typedef std::vector<Node2D> vectorPathList;
	typedef std::vector<Node2D>::iterator vectorPathListIter;

private:
	GameMap*		_gameMap;

	vectorOpenList	_vOpenList;
	vectorCloseList _vCloseList;
	vectorPathList	_vPathList;

	Node2D			_startPoint;
	Node2D			_endPoint;

	bool _isFindedToGoal;
	bool _isFindedPath;

	bool _neartilecollision;
	cocos2d::Point _aimPoint;

public:

	Astar();
	Astar(GameMap * map);
	~Astar();
	
	bool init(Node2D start, Node2D end);
	void release();
	void releaseExclusiveofPath();
	void update();
	void render();
	void pathFinder();
	void openNode(int idX, int idY, searchNodeInfo* parentNode, float ChildCostG);

	void setPathFinder(bool _is) { this->_isFindedPath = _is; }
	
	cocos2d::Point getAimPoint() { return _aimPoint; }
	bool getNearTileColl() { return _neartilecollision; }
	searchNodeInfo* getNextNode();

	inline vectorPathList getVPathList()
	{
		return _vPathList;
	}

	DIRECTION checkPathAndReturnNextNode(cocos2d::Point spritepoint);

};