#pragma once

#include <cmath>

typedef struct NodeVector2D
{
	int nX;
	int nY;

	NodeVector2D() : nX(0), nY(0) {}
	NodeVector2D(int x, int y) : nX(x), nY(y) {}
}Node2D;

inline bool checkOverlapPoint(int nX1, int nY1, int nX2, int nY2)
{
	if (nX1 == nX2 && nY1 == nY2)
		return true;
	return false;
}

inline bool checkOverlapPoint(Node2D node1, Node2D node2)
{
	if (node1.nX == node2.nX && node1.nY == node2.nY)
		return true;
	return false;
}

class searchNodeInfo
{
private:
	Node2D			_nodeVector;
	float			_costG;
	float			_costH;

	searchNodeInfo*	_parentNode;

public:
	inline float getCostF(void) { return (_costG + _costH); }
	inline float getCostG(void) { return _costG; }
	inline float getCostH(void) { return _costH; }
	inline searchNodeInfo* getParentNode(void) { return _parentNode; }

	inline Node2D getVector(void) { return _nodeVector; }
	inline float getVecX(void) { return _nodeVector.nX; }
	inline float getVecY(void) { return _nodeVector.nY; }

	inline void setCostG(float cost) { _costG = cost; }
	inline void setCostH(Node2D endNodeVector)
	{
		int distX = std::abs(endNodeVector.nX - _nodeVector.nX);
		int distY = std::abs(endNodeVector.nY - _nodeVector.nY);

		_costH = (distX + distY);
	}

//	inline void release() { delete _parentNode; }

	searchNodeInfo(Node2D vec, searchNodeInfo* parentNode = NULL)
		: _nodeVector(vec), _parentNode(parentNode), _costG(0), _costH(0) {}
	searchNodeInfo()
	{
		_parentNode = NULL;
	}
};