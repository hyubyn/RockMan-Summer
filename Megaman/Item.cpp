#include "Item.h"


CItem::CItem()
{
	_position = D3DXVECTOR2(0, 0);
	_centerposition = D3DXVECTOR2(0, 0);
	_size = D3DXVECTOR2(0, 0);
}

RECT CItem::GetBoundingRectangle(){
	RECT boundingRect;
	boundingRect.left = _position.x;
	boundingRect.top = _position.y;
	boundingRect.right = boundingRect.left + _size.x;
	boundingRect.bottom = boundingRect.top + _size.y;

	return boundingRect;
}

D3DXVECTOR2 CItem::GetPositionCenter()
{
	return D3DXVECTOR2(_position.x/* + _origin.x*/, _position.y/* + _origin.y*/);
}

CItem::~CItem()
{

}
