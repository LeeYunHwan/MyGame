#include "AstarAlgorithm.h"

Astar::Astar()
{
}

Astar::Astar(GameMap* map)
{
	_gameMap = map;
	_isFindedPath = false;
	_neartilecollision = false;
}

Astar::~Astar()
{
}

bool Astar::init(Node2D start, Node2D end)
{
	if (checkOverlapPoint(start, end))
		return false;

	_neartilecollision = false;

	if (_gameMap->getAttribute(end.nX, end.nY))
	{
		_neartilecollision = true;
		this->_aimPoint = cocos2d::Point(end.nX, --end.nY);
		if (_gameMap->getAttribute(end.nX, end.nY))
		{
			this->_aimPoint = cocos2d::Point(end.nX, end.nY = end.nY + 2);
			if (_gameMap->getAttribute(end.nX, end.nY ))
			{
				this->_aimPoint = cocos2d::Point(--end.nX, end.nY = end.nY - 1);
				if (_gameMap->getAttribute(end.nX, end.nY))
				{	
					this->_aimPoint = cocos2d::Point(end.nX = end.nX + 2, end.nY);
					if (_gameMap->getAttribute(end.nX , end.nY))
					{
						_neartilecollision = false;
						return false;
					}
				}
			}
		}
	}

	if (_isFindedPath)
	{
		cocos2d::log("NotFindPath");
		return false;
	}

	this->release();

	_startPoint = start;
	_endPoint = end;
	_isFindedPath = true;
	searchNodeInfo* startNode;

	startNode = new searchNodeInfo(_startPoint, NULL);
	_vOpenList.push_back(startNode);

	return true;
}

void Astar::release()
{
	_startPoint = { 0,0 };
	_endPoint = { 0,0 };

	vectorOpenListIter openIter = _vOpenList.begin();

	for (; openIter != _vOpenList.end(); )
	{
		if (*openIter != NULL)
		{
			delete (*openIter);
			(*openIter) = NULL;
//			openIter = _vOpenList.erase(openIter);
		}
		else
			++openIter;
	}
	_vOpenList.clear();

	vectorCloseListIter closeIter = _vCloseList.begin();

	for (; closeIter != _vCloseList.end(); )
	{
		if (*closeIter != NULL)
		{
			delete (*closeIter);
			(*closeIter) = NULL;
//			closeIter = _vCloseList.erase(openIter);
		}
		else
			++closeIter;

	}
	_vCloseList.clear();


	vectorPathListIter pathIter = _vPathList.begin();

	for (; pathIter != _vPathList.end(); )
	{
		if (&pathIter != NULL)
			pathIter = _vPathList.erase(pathIter);
		else
			++pathIter;
	}
	_vPathList.clear();
}

void Astar::releaseExclusiveofPath()
{
	_startPoint = { 0,0 };
	_endPoint = { 0,0 };

	vectorOpenListIter openIter = _vOpenList.begin();

	for (; openIter != _vOpenList.end(); )
	{
		if (*openIter != NULL)
		{
			delete (*openIter);
			(*openIter) = NULL;
//			openIter = _vOpenList.erase(openIter);
		}
		else
			++openIter;
	}
	_vOpenList.clear();

	vectorCloseListIter closeIter = _vCloseList.begin();

	for (; closeIter != _vCloseList.end(); )
	{
		if (*closeIter != NULL)
		{
			delete (*closeIter);
			(*closeIter) = NULL;
//			closeIter = _vCloseList.erase(closeIter);
		}
		else
			++closeIter;

	}
	_vCloseList.clear();

	_isFindedPath = false;
}

void Astar::update()
{
	if (_isFindedPath == false)
		return;

	pathFinder();

}

void Astar::render(void)
{

}

void Astar::pathFinder()
{

	if (_vCloseList.size() > 120)
		return;

	searchNodeInfo* node = getNextNode();
	if (node == NULL)
		return;

	if (checkOverlapPoint(node->getVector(), _endPoint))
	{
		_isFindedPath = true;

		searchNodeInfo* getPathNode;

		for (getPathNode = node; getPathNode != NULL; getPathNode = getPathNode->getParentNode())
		{
			_vPathList.push_back(getPathNode->getVector());
		}
		_vPathList.pop_back();

		releaseExclusiveofPath();

	}
	else
	{
		openNode(node->getVecX() + 1, node->getVecY(), node, node->getCostG() + 1);
		openNode(node->getVecX() , node->getVecY() + 1, node, node->getCostG() + 1);
		openNode(node->getVecX() - 1, node->getVecY(), node, node->getCostG() + 1);
		openNode(node->getVecX() , node->getVecY() - 1, node, node->getCostG() + 1);

		pathFinder();
	}
}

void Astar::openNode(int idX, int idY, searchNodeInfo* parentNode, float childCostG)
{
	if (idX < 0 || idX >= _gameMap->getSizeX())
		return;

	if (idY < 0 || idY >= _gameMap->getSizeX())
		return;

	if (_gameMap->getAttribute(idX, idY) == 1)
		return;

	for (int i = 0; i < _vCloseList.size(); i++)
	{
		if (checkOverlapPoint(idX, idY, _vCloseList[i]->getVecX(), _vCloseList[i]->getVecY()))
			return;
	}

	for (int i = 0; i < _vOpenList.size(); i++)
	{
		if (checkOverlapPoint(idX, idY, _vOpenList[i]->getVecX(), _vOpenList[i]->getVecY()))
			return;
	}

	searchNodeInfo*	childNode;
	childNode = new searchNodeInfo({ idX, idY }, parentNode);
	childNode->setCostG(childCostG);
	childNode->setCostH(_endPoint);
	_vOpenList.push_back(childNode);
}

searchNodeInfo* Astar::getNextNode()
{
	float tempCostf = 9999;
	int tempIndex = -1;

	searchNodeInfo* nextNode = NULL;

	for (int i = 0; i < _vOpenList.size(); i++)
	{
		if (tempCostf >= _vOpenList[i]->getCostF())
		{
			tempCostf = _vOpenList[i]->getCostF();
			tempIndex = i;
		}
	}

	if (tempIndex >= 0)
	{
		nextNode = _vOpenList[tempIndex];
		_vCloseList.push_back(nextNode);
		_vOpenList.erase(_vOpenList.begin() + tempIndex);
	}

	return nextNode;
}


DIRECTION Astar::checkPathAndReturnNextNode(cocos2d::Point spritepoint)
{
	DIRECTION direction = NOTDIRECTION;
	bool _issetdirection = false;
	if (!_vPathList.empty())
	{
		Node2D nextNode(_vPathList[_vPathList.size() - 1]);
		
		if (!_issetdirection  && spritepoint.x > nextNode.nX  )
		{
			direction = LEFT;
			_issetdirection = true;
		}
		if (!_issetdirection && spritepoint.x < nextNode.nX )
		{
			direction = RIGHT;
			_issetdirection = true;
		}
		if (!_issetdirection && spritepoint.y> nextNode.nY)
		{
			direction = BACK;
			_issetdirection = true;
		}
		if (!_issetdirection && spritepoint.y < nextNode.nY)
		{
			direction = FRONT;
			_issetdirection = true;
		}

		_vPathList.pop_back();

	}

	return direction;
}


