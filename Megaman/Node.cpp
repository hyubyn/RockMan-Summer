#include "Node.h"



CNode::CNode(void)
{
}


CNode::~CNode(void)
{
}

CNode::CNode(INT32 id, int x, int y, int width, int height, int count, vector<int> listId)
{
	_lt = NULL;
	_lb = NULL;
	_rt = NULL;
	_rb = NULL;
	_nodeId = id;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_objectCount = count;
	for (int i = 0; i < listId.size(); ++i)
	{
		_listObjectId.push_back(listId.at(i));
	}
}

CNode::CNode(INT32 id, int x, int y, int width, int height)
{
	_lt = NULL;
	_lb = NULL;
	_rt = NULL;
	_rb = NULL;
	_nodeId = id;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	
}

Box CNode::GetBox()
{
	return Box(_x, _y, _width, _height, 0.0f, 0.0f);
}

int CNode::ClipCamera(RECT viewport)
{
	Box thisBox = GetBox();
	Box objBox;
	objBox._x = viewport.left;
	objBox._y = viewport.top;
	objBox._width = viewport.right - viewport.left;
	objBox._height = viewport.top - viewport.bottom;

	if (thisBox.IntersecWith(objBox))
	{
		return 1;
	}
	return 0;
}

void CNode::AddObject(CGameObject* object)
{
	_listGameObject.push_back(object);
}