#ifndef _NODE_H_
#define _NODE_H_
#include "CGameObject.h"

using namespace std;


class CNode
{
	public:
	INT32 _nodeId;
	CNode* _lt;
	CNode* _rt;
	CNode* _lb;
	CNode* _rb;
	int _objectCount;
	vector<int> _listObjectId;
	vector<CGameObject*> _listGameObject;
	int _x, _y, _width, _height;
	Box GetBox();
	CNode(void);
	CNode(INT32, int, int, int, int, int, vector<int>);
	CNode(INT32, int, int, int, int);
	int ClipCamera(RECT viewPort);
	void AddObject(CGameObject*);
	~CNode(void);
};

#endif