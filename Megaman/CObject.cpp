#include "CObject.h"

CObject::CObject(){
	_position = D3DXVECTOR2(0, 0);
	_origin = D3DXVECTOR2(0, 0);
	_size = D3DXVECTOR2(0, 0);
}

CObject::~CObject(){

}

void CObject::UpdateBox()
{
	 _box._x = _position.x;
	 _box._y = _position.y;
	 _box._width = _size.x;
	 _box._height = _size.y;
	 _box._vx = 0.0f;
	 _box._vy = 0.0f;
}

Box CObject::GetBox()
{
	if (_box._x == NULL)
	{
		int a = 0;
		return Box(0,0,0,0,0,0);
	}
	return _box;
}

RECT CObject::GetBoundingRectangle(){
	RECT boundingRect;
	boundingRect.left = _position.x;
	boundingRect.top = _position.y;
	boundingRect.right = boundingRect.left + _size.x;
	boundingRect.bottom = boundingRect.top + _size.y;

	return boundingRect;
}

D3DXVECTOR2 CObject::GetPositionCenter()
{
	return D3DXVECTOR2(_position.x, _position.y);
}